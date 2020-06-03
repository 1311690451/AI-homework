clear ,clc;
sign = [2 8 3;
        1 6 4;
        7 0 5];
target = [1 2 3;
         7 8 4;
         0 6 5];

past = 1;     
max = 5;
layer = 1; 	
NO = 1; 	
parents(layer).date(NO).c = sign; 	
flag=0;		
search(layer)=1; 	
iteration=0;   % 记录循环次数
step = 0;

while flag==0 && iteration<10   % 防止循环超过10次死机
    for i = 1 : past
        step = step + 1;
        search(layer) = i;
        
        matrix = parents(layer).date(i).c;
        [rows ,cols] = find(matrix==0);
        
        dir = direction(rows ,cols);
        
        for t = 1 : 4
            if dir(t) == 0
                parents(layer+1).date(NO).c = move(matrix ,t);
                NO = NO + 1;
            end
        end
        
        for n = 1:NO-1
            A = parents(layer+1).date(n).c;
            if isequal(A, target) == 1
                flag = 1;
                search(layer + 1) = n;
                break;
            end
%             %删除重复
%             if layer >= 2
%                 for m = 1:past-1
%                     if parents(layer).date(m).c == parents(layer+1).date(n).c
%                         parents(layer+1).date(n).c = parents(layer+1).date(n+1).c;
%                         
%                         if n == NO
%                             parents(layer+1).date(n).c=zeros(4 ,4);
%                         end
%                     end
%                 end
%             end
        end
        
        if flag==1
            break;
        end
        
    end
    layer = layer + 1;
	past = NO-1;
	NO = 1;
	iteration = iteration+1;
end



