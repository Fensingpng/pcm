%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%1(��������� �������������)
fid = fopen('12333.pcm');
osn = fread(fid,'int16');
y = complex(osn(1:2:end),osn(2:2:end));
fclose(fid);

subplot(2,1,1);
plot(real(y(:,:)));%����������� ������ ������������������� �������
grid on;
xlabel('�����');
ylabel('���������');
title('��������� �������������');



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5(���)



subplot(2, 2, 3);
[corr, lags] = xcorr(y, 'coeff');
plot(lags,corr);
grid on;
xlabel('Lags');
ylabel('��������������');
title('������������������ �������������');

[~, lag] = max(corr);
repeatedPart = y(lag:end);
subplot(2, 2, 4);
plot(repeatedPart);
title('������������� �����');
xlabel('�����');
ylabel('���������');







