%%  ѵ������ģ��
global w b

% w,b ����ڣ�0��5����Χ��ȡֵ
w = rand(1, size(X, 2)) * 5;
b = rand(1) * 5;

w_time = zeros(times, size(X,2));
b_time = zeros(1, times);

for i = 1:times
    m = size(X, 1);
    deta_w = (1/m) * (Y' - w*X' - b) * (-X);
    deta_b = (1/m) * sum((Y' - w*X' - b) * (-1));
    w = w - eta*deta_w; % ����
    b = b - eta*deta_b;
	w_time(i,:) = w; % ��¼
    b_time(i) = b;
end
