A=readtable('../data/N=512、4096点的一维信号.xlsx','ReadVariableName',false,'Range','A1:A512').(1);
C=readtable('../data/N=512、4096点的一维信号.xlsx','ReadVariableName',false,'Range','C1:C4096').(1);
fftA = fft(A);
fftC = fft(C);
h5create("../data/fft1_512.h5", "/data512", size(A))
h5write("../data/fft1_512.h5","/data512",A)
h5create("../data/fft1_4096.h5", "/data4096", size(C))
h5write("../data/fft1_4096.h5","/data4096",C)
h5create("../data/fft1_512.h5", "/fft512_r", size(real(fftA)))
h5write("../data/fft1_512.h5","/fft512_r",real(fftA))
h5create("../data/fft1_512.h5", "/fft512_i", size(imag(fftA)))
h5write("../data/fft1_512.h5","/fft512_i",imag(fftA))
h5create("../data/fft1_4096.h5", "/fft4096_r", size(real(fftC)))
h5write("../data/fft1_4096.h5","/fft4096_r",real(fftC))
h5create("../data/fft1_4096.h5", "/fft4096_i", size(imag(fftC)))
h5write("../data/fft1_4096.h5","/fft4096_i",imag(fftC))