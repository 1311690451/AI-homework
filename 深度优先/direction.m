function dir = direction(r,c)
%UNTITLED3 此处显示有关此函数的摘要
%   此处显示详细说明
% 上
dir = zeros(1 ,4);
if r - 1 < 1
    dir(1) = 1;
end

% 下
if r + 1 > 3
	dir(2) = 1;
end

% 左
if c - 1 <1
	dir(3) = 1;
end

% 右
if c + 1 > 3
	dir(4) = 1;
end
end

