data512_512 = imread("../data/512×512.jpg");
fft512_512 = fft(im2double(data512_512));
data4096_4096 = imread("../data/4096×4096.jpg");
fft4096_4096 = fft(im2double(data4096_4096));
h5create("../data/fft2_512.h5", "/data512", size(data512_512))
h5write("../data/fft2_512.h5","/data512",data512_512)
h5create("../data/fft2_4096.h5", "/data4096", size(data4096_4096))
h5write("../data/fft2_4096.h5","/data4096",data4096_4096)
h5create("../data/fft2_512.h5", "/fft512_r", size(real(fft512_512)))
h5write("../data/fft2_512.h5","/fft512_r",real(fft512_512))
h5create("../data/fft2_512.h5", "/fft512_i", size(imag(fft512_512)))
h5write("../data/fft2_512.h5","/fft512_i",imag(fft512_512))
h5create("../data/fft2_4096.h5", "/fft4096_r", size(real(fft4096_4096)))
h5write("../data/fft2_4096.h5","/fft4096_r",real(fft4096_4096))
h5create("../data/fft2_4096.h5", "/fft4096_i", size(imag(fft4096_4096)))
h5write("../data/fft2_4096.h5","/fft4096_i",imag(fft4096_4096))
