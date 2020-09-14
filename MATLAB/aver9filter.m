function [ y] = aver9filter( x )
%10点均值滤波
%数组长度必须大于10   
%输出结果n X 1向量
n = length(x);%get length
y = zeros(n,1);
y(1) =0.1*sum(x(1:10));
for k = 2:(n-9);
    y(k) = (y(k-1) + 0.1*(x(k+9) - x(k-1)));
end
for k = 1:9;
    m = n-9+k;
    y(m) = 1/(10-k)*sum(x(m:n));
end
