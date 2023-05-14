clc;close all;clear all; %#ok<*CLALL>
 
Fs = 44100; %采样频率
N = 20000; %采样点数
f=8000; %正弦波频率
t=(1:N)/Fs; %时间序列
s = sin(2*pi*f*t) ;
sound(s,Fs);
figure(1);
subplot(3,1,1);
plot(t,s,'r','LineWidth',1.2);
title('时域波形');
axis([0,100/Fs,-3,3]);
set(gca,'LineWidth',1.2);
%画频谱图
df1=Fs/(N-1);%分辨率
f1=(0:N-1)*df1;%其中每点的频率
%默认做N=4096点FFT
%不同点数的FFT的频率分辨率时不一样的，点数越多，分辨率越高
%如128点FFT即从输入信号中任选128个点进行傅里叶变换，输出结果表示频谱信息
Y1=fft(s)/sqrt(width(s));
subplot(3,1,2);
%对称频谱图的一半
plot(f1,abs(Y1),'r','LineWidth',1.2);
title('频谱图');
set(gca,'LineWidth',1.2);

%转化为位宽16bit数据
s_16bit= floor(s*2^15);
%s_16bit=s*2;
sound(s_16bit,Fs);

% %生成文件
fid= fopen('sin_data.txt','w+');
%生成有符号数，FFT需要导入有符号数
for i=1:N
    fprintf(fid,'%d',s_16bit(i));
    fprintf(fid,'\r\n');
end
%导出无符号数，十六进制
% s_16bit_hex=dec2hex(s_16bit);
%     for i=1:N
%         for j=1:4
%             fprintf(fid,'%s',s_16bit_hex(i,j));%  '%c'表示单个字符，'%s'表示字符向量，
%             if j ==4
%                 fprintf(fid,'\r\n');
%             end
%         end
%         
%     end   
fclose(fid);
 
%%
%验证导出的数据是否正确，导入绘制一下FFT
%导入十六进制数据
% a= textread('D:\work\13_LD2101\matlab\sin_data.txt','%s');
% data_hex=hex2dec(a);
% data_fft=abs(fft(data_hex));
% subplot(3,1,3);
% plot(data_fft);
%导入有符号数
a=importdata('sin_data.txt','%c');
data_fft=abs(fft(a))/sqrt(height(a));
subplot(3,1,3);
plot(data_fft);