clear, clc;
more off;

Nx = 8;
Ny = 8;

Ttop = 0.5;
Tleft = 0.5;
Tbottom = 1.0;
Tright = 0.5;

Nmax = 100;

T = zeros(Ny,Nx);

T(:,:) = Ttop;

T(1,:) = Ttop;
T(Ny,:) = Tbottom;
T(:,1) = Tleft;
T(:,Nx) = Tright;

tao = 0.08;

graphics_toolkit("gnuplot");
graphics_toolkit();

colormap(jet)

for n = 1:Nmax

  contourf([1:Nx], [1:Ny], rot90(T'));
  filename = sprintf('output/%05d.png', n);
  print(filename, "-dpng");
  
  for i = 2:Nx-1
    Told(i) = T(1,i);
  end
  
  Told(1) = T(2,1);
  Told(Nx) = T(2,Nx);
  
  for j = 2:Ny-1
    for i = 2:Nx-1      
      
      t = tao * ((Told(i) + T(j+1, i) + Told(i-1) + T(j,i+1)) - (T(j,i) * 4)) + T(j,i);
      Told(i) = T(j,i);
      
      T(j,i) = t;
    end
    
    Told(1) = T(j+1,1);
    Told(Nx) = T(j+1,Nx);
  end
end
