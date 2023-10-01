A=readtable('../data/N=512、4096点的一维信号.xlsx','ReadVariableName',false,'Range','A1:A512').(1);
C=readtable('../data/N=512、4096点的一维信号.xlsx','ReadVariableName',false,'Range','C1:C4096').(1);
fftA = fft(A);
fftC = fft(C);
save('../data/data512.mat', "A")
save('../data/data4096.mat', "C")
save('../data/fft512.mat', "fftA")
save('../data/fft4096.mat', "fftC")