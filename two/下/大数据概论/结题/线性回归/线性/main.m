
clear all
input_data % 输入。
train % 训练。

% 一维矩阵时画图。
size(X, 2)==1
    % 命令行打印
    fprintf('预测直线是：\n')
    fprintf('y = %f * x - %f \n', w, b)
    % 绘图
    figure('units','normalized','position',[0.1,0.1,0.8,0.6])
    subplot(1,2,1)
    hold on
    plot(w_time', 'r')
    plot(b_time)
    legend('w', 'b')
    xlabel('训练次数')

    subplot(1,2,2)
    hold on
    x = 0: 0.1: 10;
    for i = 1: length(x);
        y(i) = w*x(i) + b;
    end
    plot(x, y, 'r');
    plot(X, Y, 'o');
    xlabel('x')
    ylabel('y')


