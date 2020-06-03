clear,clc;
% Index = input('请输入LS LN P(H) P(E)');
Index = [800 0.7 0.6 0.4];
P1 = (Index(1) * Index(3)) / ((Index(1) - 1) * Index(3) + 1);
P0 = (Index(2) * Index(3)) / ((Index(2) - 1) * Index(3) + 1);

figure(1);
aIndexis([0 1.1 0 1.1]);
line([0 Index(4)] ,[P0 Index(3)],'color' , 'k' ,'linewidth' ,2);

line([Index(4) 1] ,[Index(3) P1] ,'color' , 'k' ,'linewidth' ,2);
line([Index(4) Index(4)] ,[0 Index(3)] ,'linestyle' ,':');
line([0 Index(4)] ,[Index(3) Index(3)] ,'linestyle' ,':');
line([1 1] ,[0 P1] ,'linestyle' ,':');
line([0 1] ,[P1 P1] ,'linestyle' ,':');

title('主观BAYES');
teIndext(0 ,P0 ,'P(H/~E)');
teIndext(0 ,Index(3) ,'P(H)');
teIndext(0 ,P1 ,'P(H/S)');
teIndext(Index(4) ,0 ,'P(E)');

Indexlabel('P(E/S)');
ylabel('P(H/S)');
grid;