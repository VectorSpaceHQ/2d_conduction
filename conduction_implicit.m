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
  
  for j = 2:Ny-1
    for i = 2:Nx-1      
      T(j, i) = (T(j-1, i) + T(j+1, i) + T(j, i-1) + T(j, i+1)) / 4;
    end
  end
  
end