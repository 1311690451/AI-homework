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
iteration=0;   % ��¼ѭ������
step = 0;

while flag==0 && iteration<100   % ��ֹѭ������100������
    for i = 1 : past
        step = step + 1;
        search(NO) = result;
        
        matrix = parents(layer).date(i).c;
        [rows ,cols] = find(matrix==0);
        
		%��û�����Ƶ��ƶ����ų���һ�ε��ƶ��������ֹ�ص���һ��״̬
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
        
        
        %��������һ�����ȼ�������ʹ��������������Ľ��У�����һ����֧����
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
        
            %�б����磬�˳��ж�
            A = parents(layer).date(NO-1).c;
            if isequal(A, target)
                flag = 1;
                fprintf("ʵ��ɹ���");
                break;
            end
            
            %�б��ظ�����
            for m = 1:past-1
                %������û�ظ�
                if parents(layer).date(m).c == parents(layer).date(NO-1).c    
                      NO = NO - 2;
                      date = 2;   
                else date = 1;  %ǿ���л��任״̬       
                end
            end
        
        if flag==1%ǿ���˳����ټ�һ�㱣��
            break;
        end
        
        search(NO) = result;%�����ƶ��Ĺ켣
        
    end
    
    if isequal(dir ,ones(1 ,4))             %��ֹû�е�·����
        layer = layer + 1;
    end
    
	past = NO;                              %������û��ɶ��

	iteration = iteration+1;
end