%%%Overall Analysis for Vehicle Design Parameters
%%Jan 16 2018
%%Svena Yu
%%UBC Solar

%%Constants
g = 9.81; %m/s^2

%%Param
%T = trackwidth
%W = weight
%COG_z = z height of centre of gravity
%COG_y
%COG_x
%SSF = Static stability factor

%Lowerbound of trackwidth=0.8m
%Upperbound of trackwidth=2m
T_low=0.8;
T_high=2;
n=round((2-0.8)/0.1+1, 0);
T=linspace(T_low,T_high,n);

%Lower bound of centre of gravity height=0.1m
%Upperbound of centre of gravity height=0.6m
COG_z = linspace(0.2,0.6,n);

%Lowerbound of total weight=120kg;
%Upperbound of total weight=200kg;
W = linspace(120,200,n);

%SSF Columns (j) = COG_z
%SSF Rows (i) = T
SSF=eye(n);
for i=1:n
    for j=1:n
    SSF(i,j)= T(i)/(2*COG_z(j));
    end
end

%%Calculating overturning velocity
%%v = sqrt(T*g*r/(4*COG_z))

%Lowerbound radius of turning=6m
%Upperbound radius of turning=9m
r = linspace(6,9,n);

%Chosen SSF Column -> row vector
%Changing COG_z
SSF_col = transpose(SSF(:,1));
%Chosen SSF Row
%Changing T (trackwidth)
SSF_row = SSF(1,:);

%v Column (j)= SSF_col/row 
%v Row (i)= r
v=eye(n);
for i=1:n
    for j=1:n
        v(i,j)= (SSF_col(j)*g*r(i)/2)^(1/2);
    end
end
%Comment: There should be a value > 16.7m/s or 60km/h
%especially in the first few columns

v
r
T


