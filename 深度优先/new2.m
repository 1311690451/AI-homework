clear ,clc;
sign = [2 8 3;
        1 0 4;
        7 6 5];
target = [1 2 3;
         7 8 4;
         0 6 5];

past = 1;     
max = 5;
layer = 1; 	
date = 1;
NO = 1; 	
result = 0;

parents(layer).date(NO).c = sign; 	
flag=0;		
search(layer)=1; 	
iteration=0;   % 记录循环次数
step = 0;

while flag==0 && iteration<100   % 防止循环超过100次死机
    for i = 1 : past
        step = step + 1;
        search(NO) = result;
        
        matrix = parents(layer).date(i).c;
        [rows ,cols] = find(matrix==0);
        
		%再没有限制得移动和排除上一次得移动情况，防止回到上一个状态
        if date == 1
            dir = direction(rows ,cols);
        else 
            dir = direction(rows ,cols);
            if result == 1
                dir(2) = 1;
            end 
            if result == 2
                dir(1) = 1;
            end
            if result == 3
                dir(4) = 1;
            end
            if result == 4
                dir(3) = 1;
            end
        end
        
        
        %这里设置一下优先级，可以使得搜索可以有序的进行，沿着一个分支进行
        if dir(1) == 0
            parents(layer).date(NO).c = move(matrix ,1);
            NO = NO + 1;
            result = 1;
        elseif dir(2) == 0
            parents(layer).date(NO).c = move(matrix ,2);
            NO = NO + 1;
            result = 2;
        elseif dir(3) == 0
            parents(layer).date(NO).c = move(matrix ,3);
            NO = NO + 1;
            result = 3;
        elseif dir(4) == 0
            parents(layer).date(NO).c = move(matrix ,4);
            NO = NO + 1;
            result = 4;
        end
        
            %判别网络，退出判定
            A = parents(layer).date(NO-1).c;
            if isequal(A, target)
                flag = 1;
                fprintf("实验成功！");
                break;
            end
            
            %判别重复网络
            for m = 1:past-1
                %瞧瞧重没重复
                if parents(layer).date(m).c == parents(layer).date(NO-1).c    
                      NO = NO - 2;
                      date = 2;   
                else date = 1;  %强行切换变换状态       
                end
            end
        
        if flag==1%强制退出，再加一层保险
            break;
        end
        
        search(NO) = result;%看下移动的轨迹
        
    end
    
    if isequal(dir ,ones(1 ,4))             %防止没有道路可走
        layer = layer + 1;
    end
    
	past = NO;                              %理论上没有啥用

	iteration = iteration+1;
end