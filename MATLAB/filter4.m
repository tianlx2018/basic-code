function [ y] = filter4( x )
%4���ֵ�˲�
%���鳤�ȱ������4   
%������n X 1����
n = length(x);%get length
y = zeros(n,1);
y(1) =0.25*(x(1)+x(2)+x(3)+x(4));
for k = 2:(n-3);
    y(k) = (y(k-1) + 0.25*(x(k+3) - x(k-1)));
end
for k = 1:3;
    m = n-3+k;
    y(m) = 1/(4-k)*sum(x(m:n));
end