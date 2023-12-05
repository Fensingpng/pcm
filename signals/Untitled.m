%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%1(��������� �������������)
fid = fopen('12333.pcm');
osn = fread(fid,'int16');
y = complex(osn(1:2:end),osn(2:2:end));
fclose(fid);

subplot(3,2,1);
plot(real(y(:,:)));%����������� ������ ������������������� �������
grid on;
xlabel('�����');
ylabel('���������');
title('��������� �������������');


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%2(��������� �������������)
Fs=64;  %!!!

spec = abs (fft(y));
spec = spec (1:end/2);
freq = (Fs/2)*(1:length(spec))/length(spec);
subplot(3,2,2);
plot (freq, spec);
xlabel ('�������');
ylabel ('���������');
title('��������� �������������');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%3(����� �������)
fid1 = fopen('����� 1.pcm');
osn1 = fread(fid1,'int16');
chast1 = complex(osn1(1:2:end),osn1(2:2:end));
fclose(fid1);

subplot(3,2,3);
plot(real(chast1(:,:)));
grid on;
xlabel('�����');
ylabel('���������');
title('����� 1');


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%4


% ������� ���������� ����
snr_level = 0,01;  % ��������� ������-��� � ���������
% ���������� ����
t = 0:0.1:10;

noisy_signal = awgn(chast1, snr_level, 'measured');

subplot(3,2,4);
plot(real(noisy_signal));
grid on;
title('������ � ����������� �����');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5(��� ����� �������)




%[c,lags]=xcorr(chast1, 'coeff');  ��������������� ���
[c,lags]=xcorr(chast1);
subplot(3,2,5);
plot(lags, c);
grid on;
title('���');



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%(��� ����� ������� � �����)


[c,lags]=xcorr(noisy_signal);
subplot(3,2,6);
plot(lags, c);
grid on;
title('��� � �����');









