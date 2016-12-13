clear, clc;
more off;

Nx = 8;
Ny = 8;

Ttop = 0.5;
Tleft = 0.5;
Tbottom = 1.0;
Tright = 0.5;

Nmax = 10;


T = zeros(Nx,Ny);

Tavg = (Ttop + Tleft + Tbottom + Tright) / 4;

T(:,:) = Tavg;

T(1,:) = Tleft;
T(Nx,:) = Tright;
T(:,1) = Ttop;
T(:,Ny) = Tbottom;

colormap(jet)

for n = 1:Nmax
  
  contourf([1:Nx], [1:Ny], rot90(T));
  pause(0.1)
  
  for i = 2:Nx-1
    Told(i) = T(1,i);
  end
  
  Told(1) = T(2,1);
  Told(Nx) = T(2,Nx);
  
  for j = 2:Ny-1
    for i = 2:Nx-1      
      
      t = (Told(i) + T(j+1, i) + Told(i-1) + T(j,i+1)) / 4;
      
      Told(i) = T(j,i);
      
      T(j,i) = t;
    end
    
    Told(1) = T(j+1,1);
    Told(Nx) = T(j+1,Nx);
    
  end
end