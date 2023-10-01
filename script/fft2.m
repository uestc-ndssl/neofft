data512_512 = imread("../data/512×512.jpg");
fft512_512 = fft(im2double(data512_512));
data4k_4k = imread("../data/4096×4096.jpg");
fft4k_4k = fft(im2double(data4k_4k));
save('../data/data512_512.mat', "data512_512")
save('../data/data4k_4k.mat', "data4k_4k")
save('../data/fft512_512.mat', "fft512_512")
save('../data/fft4k_4k.mat', "fft4k_4k")