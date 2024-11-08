
clear all
input_data % ���롣
train % ѵ����

% һά����ʱ��ͼ��
size(X, 2)==1
    % �����д�ӡ
    fprintf('Ԥ��ֱ���ǣ�\n')
    fprintf('y = %f * x - %f \n', w, b)
    % ��ͼ
    figure('units','normalized','position',[0.1,0.1,0.8,0.6])
    subplot(1,2,1)
    hold on
    plot(w_time', 'r')
    plot(b_time)
    legend('w', 'b')
    xlabel('ѵ������')

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


