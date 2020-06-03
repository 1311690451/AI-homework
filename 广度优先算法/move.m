function newMatrix = move(oldMatrix,direction)
%UNTITLED2 此处显示有关此函数的摘要
%  % n=1上，n=2下，n=3左，n=4右
n = direction;
[rows ,cols] = find(oldMatrix == 0);

if n == 1
    matrix1=oldMatrix;
	buff = matrix1(rows-1,cols);
    matrix1(rows-1,cols)=0;
	matrix1(rows,cols)=buff;
end

if n == 2
	matrix1=oldMatrix;
	buff = matrix1(rows+1,cols);
    matrix1(rows+1,cols)=0;
	matrix1(rows ,cols)=buff;
end

if n == 3
	matrix1=oldMatrix;
	buff = matrix1(rows,cols-1);
    matrix1(rows,cols-1)=0;
	matrix1(rows ,cols)=buff;
end

if n == 4
    matrix1=oldMatrix;
	buff = matrix1(rows,cols+1);
    matrix1(rows,cols+1)=0;
	matrix1(rows ,cols)=buff;
end
	
   newMatrix = matrix1;

end

