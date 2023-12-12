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



subplot(2, 1, 2);
[corr, lags] = xcorr(y, 'coeff');
plot(lags,corr);
grid on;
xlabel('Lags');
ylabel('Автокорреляция');
title('Автокорреляционное представление');


[R, lags] = xcorr(y);

[max_val, max_idx] = max(abs(R)); 

repeated_start = max_idx - length(y) + 1;
repeated = y(repeated_start:end);
figure();
subplot(1,1,1);
plot(real(repeated));
grid on;
xlabel('Sample');
ylabel('Amplitude');
title('Повторяющаяся часть сигнала');






