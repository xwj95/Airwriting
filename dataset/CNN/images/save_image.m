n = 44;
c = trainX(:, n);
%c = train_x(:, n);
%imshow(reshape(c, 28, 28)');
imshow(reshape(c, 100, 100)');
disp(trainY(n));
%disp(train_y(n));
fid = fopen('image.txt', 'w');
for i = 1:10000
    fprintf(fid, '%.1f ', c(i));
end
