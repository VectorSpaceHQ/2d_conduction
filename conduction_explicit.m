clear, clc;
more off;

Nx = 32;
Ny = 24;

Ttop = 0.5;
Tleft = 0.5;
Tbottom = 1.0;
Tright = 0.5;

Nmax = 1000;


T = zeros(Ny,Nx);

Tavg = (Ttop + Tleft + Tbottom + Tright) / 4;

#T(:,:) = Tavg;

T(1,:) = Ttop;
T(Ny,:) = Tbottom;
T(:,1) = Tleft;
T(:,Nx) = Tright;

colormap(jet)

tao = 0.08;

for n = 1:Nmax

  #contourf([1:Nx], [1:Ny], rot90(T'));
  #pause(0.001)

  
  for i = 2:Nx-1
    Told(i) = T(1,i);
  end
  
  Told(1) = T(2,1);
  Told(Nx) = T(2,Nx);
  
  #Told = T;
  
  for j = 2:Ny-1
    for i = 2:Nx-1      
      
      #t = tao * ((Told(j-1,i) + Told(j+1, i) + Told(j,i-1) + Told(j,i+1)) - (Told(j,i) * 4)) + Told(j,i);
      t = tao * ((Told(i) + T(j+1, i) + Told(i-1) + T(j,i+1)) - (T(j,i) * 4)) + T(j,i);
      Told(i) = T(j,i);
      
      T(j,i) = t;
    end
    
    Told(1) = T(j+1,1);
    Told(Nx) = T(j+1,Nx);
  end
end

contourf([1:Nx], [1:Ny], rot90(T'));