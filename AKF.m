%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%1(Временное представление)
fid = fopen('12333.pcm');
osn = fread(fid,'int16');
y = complex(osn(1:2:end),osn(2:2:end));
fclose(fid);

subplot(2,1,1);
plot(real(y(:,:)));%Отоброжение только действительнойчасти сигнала
grid on;
xlabel('Время');
ylabel('Амплитуда');
title('Временное представление');



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5(АКФ)



subplot(2, 2, 3);
[corr, lags] = xcorr(y, 'coeff');
plot(lags,corr);
grid on;
xlabel('Lags');
ylabel('Автокорреляция');
title('Автокорреляционное представление');

[~, lag] = max(corr);
repeatedPart = y(lag:end);
subplot(2, 2, 4);
plot(repeatedPart);
title('Повторяющаяся часть');
xlabel('Время');
ylabel('Амплитуда');







