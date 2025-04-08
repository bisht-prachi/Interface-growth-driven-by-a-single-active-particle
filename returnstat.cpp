
/***Prachi Bisht. Program created on 28/10/2018 ***/
/*** Return Statistics Study */
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <random>

#define n 8000
#define m 1
#define eps 5e-2


std::mt19937 gen{static_cast<long unsigned int>(time(0))};
std::uniform_int_distribution<int> dist_n(0,n-1);
std::uniform_real_distribution<double> dist_u(0,1);


void gen_lattice_arr(int *lattice)
{
	
    for (int i=0; i<n; i=i+2) lattice[i] = -1;  
    for (int i=1; i<n; i=i+2) lattice[i] = 1;

//	int h = n/2;
//    for (int i=0; i<h; i=i+1) lattice[i] = -1;  
//    for (int i=h; i<n; i=i+1) lattice[i] = 1;

//    for (int i=0; i<n; i=i+1) lattice[i] = 1;
//    int r = 0; int y = 0;
//    do
//    {
//        r = dist_n(gen);
//        if(lattice[r]!=-1)
//            lattice[r]=-1;
//        else continue;

//        y++;
//    }while(y<(n/2));

}



void gen_particle_arr(int *particle)
{

      particle[0] = n/2;//dist_n(gen);

}



int search_sites(int particle[m], int r)
{
    int number=0;
    for(int i =0; i<m; i++)
    {
        if (particle[i]==r) number+=1;

    }

    return number;
}




int search_particle(int dummy_bond, int particle[m])
{
    if (particle[0]==dummy_bond)
        return 1;
    else
        return 0;

}



void update_surface (int *particle, int *lattice, double *height, int (*search_sites)(int*, int))
{
	       ///begin particle update///
	    
	       int r = particle[0] - 1;
	       if (particle[0]==0) r = n-1;
	                   	       
               	
//               	sites_visits[r] +=1;
               		
		       if(lattice[r]==-1)
		       {

		               if(r!=n-1 && lattice[r+1]==1)
		               {

				               lattice[r]*=-1;
				               lattice[r+1]*=-1;
       			                       height[r+1] += 2;
//       			                       flips += 1;


		               }

		               else if(r==n-1 && lattice[0]==1)
		               {
		                
				               lattice[r]*=-1;
				               lattice[0]*=-1;
			                       height[0] += 2;
//			                       flips += 1;
		               }

		       } 
		       

}


void update_particle( int *particle, int *lattice )
{

               ///begin particle update///

           int dummy = particle[0];

            
               if(dummy!=n-1 & dummy!=0)
               {
                    if(lattice[dummy-1]==1 & lattice[dummy]==-1)
                    {

                        double b = dist_u(gen);

                        if( b>0.5)
                        {
                          particle[0] =  dummy + 1;

                        }

                        else if (b<=0.5)
                        {
                          particle[0] =  dummy - 1;
                        }


                    }

                    else if(lattice[dummy-1]==-1 & lattice[dummy]==-1)
                    {
                         particle[0] =  dummy + 1;
                    }

                    else if(lattice[dummy-1]==1 & lattice[dummy]==1)
                    {
                         particle[0] =  dummy - 1;
                    }



               }

               else if(dummy==n-1)
               {
                    if(lattice[dummy-1]==1 & lattice[dummy]==-1)
                    {

                        double b = dist_u(gen);

                        if(b>0.5)
                        {
                          particle[0] =  0;
                        }
                        else if (b<=0.5)
                        {
                          particle[0] =  dummy - 1;
                        }


                    }

                    else if(lattice[dummy-1]==-1 & lattice[dummy]==-1)
                    {
                         particle[0] =  0;
                    }

                    else if(lattice[dummy-1]==1 & lattice[dummy]==1)
                    {
                         particle[0] =  dummy - 1;
                    }



               }

               else if(dummy==0)
               {
                   if(lattice[n-1]==1 & lattice[dummy]==-1)
                    {

                        double b = dist_u(gen);

                        if(b>0.5)
                        {
                          particle[0] =  dummy + 1;
                        }
                        else if (b<=0.5)
                        {
                          particle[0] =  n - 1;
                        }


                    }

                    else if(lattice[n-1]==-1 & lattice[dummy]==-1)
                    {
                         particle[0] =  dummy + 1;
                    }

                    else if(lattice[n-1]==1 & lattice[dummy]==1)
                    {
                         particle[0] =  n - 1;
                    }


               }
            
}




void init_height(double *height, int *lattice)
{
	height[0] = 0;
	for (int i = 1; i<n; i++)
	   height[i] = height[i-1] + lattice[i-1];
}



int main()
{
    std::ofstream fout, ffout, hout, gout, kout, lout, mout, jout, nout, pout;

    int MC = 50000, ENS = 100000, r =0, delr = 0, dummy = 0, k = 0, counter =0;
    
//    fout.open("tstart_treturn_taway50.dat", std::ios::out);
      fout.open("t_away_stats8000_mod1.dat", std::ios::out);

    int h = n/2;
    double prob_taway[MC+1] = {0.0};
    double prob_treturn[MC+1] = {0.0};
    double prob_tstart[MC+1] = {0.0};

//    int bins = 1000;
//    double taway[bins] = {0.0};
//    double treturn[bins] = {0.0};
//    double tstart[bins] = {0.0};
    
do{

    int lattice[n] = {0};
    int particle[m] = {0};
    double height[n] = {0.0};


    gen_lattice_arr(lattice);
    gen_particle_arr(particle);
    init_height(height, lattice);  
    
    int t = 0;
    int b = 0;
    int a = 0;
    
    int p,q,r =0;
    
    for (int j=1; j<=MC; j++)
        {    
        
           if (particle[0]==h && j!=1)
               {
               	 a = j-1;
               	 
               	 prob_tstart[a] += 1.0;
               	 
               	 
//               	 tstart[p] = a;
//               	 p++;
               }  

          update_surface (particle, lattice, height, (*search_sites));    
          update_particle( particle, lattice );

               
               if (particle[0]==h)
               {               	 
               	 b = j;
//               	 treturn[q] = b;
               	 prob_treturn[b] += 1.0;
               	 t = b-a;
               	 prob_taway[t] += 1;
//	         taway[r] = t;
//	         q++;
//	         r++;
		 counter++;
               }

      }///MC loop
      

  k++;
 }while(k<ENS);///history loop
 
 	for (int j=0; j<=MC; j++)
        	fout<<j<<"\t"<<prob_taway[j]/(1.0*counter)<<"\t"<<prob_tstart[j]/(1.0*counter)<<"\t"<<prob_treturn[j]/(1.0*counter)<<"\n";
        	std::cout<<counter<<"\n";


// 	for (int j=0; j<bins; j++)
//        	fout<<j<<"\t"<<tstart[j]/(1.0*ENS)<<"\t"<<treturn[j]/(1.0*ENS)<<"\t"<<taway[j]/(1.0*ENS)<<"\n";
	

gout.close();
fout.close();


return 0;
}


