/***Prachi Bisht. Program created on 28/10/2018 ***/
/***Evaluating roughness about mean surface profile */
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <random>

#define n 1024
#define m 1


std::mt19937 gen{static_cast<long unsigned int>(time(0))};
std::uniform_int_distribution<int> dist_n(0,n-1);
std::uniform_real_distribution<double> dist_u(0,1);



void gen_lattice_arr(int *lattice)
{


    for (int i=0; i<n; i=i+2) lattice[i] = -1;  
    for (int i=1; i<n; i=i+2) lattice[i] = 1;
    
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

	particle[0] = n/2;

//      particle[0] = dist_n(gen);

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


void init_height(double *height, int *lattice)
{
	height[0] = 0;
	for (int i = 1; i<n; i++)
	   height[i] = height[i-1] + lattice[i-1];
}



int main()
{
    std::ofstream fout, hout, gout, kout, lout;

    int MC = 100000, ENS = 10000, r =0, delr = 0, dummy = 0, k = 0, current = 0, counter = 0;
    double beta = -1.0, J = 0;
    fout.open("roughness_about_mean1024_mod.dat", std::ios::out);    

    double bias = 0.5;    
    
    int timestamp = MC/100;
    
    double width_ss[timestamp+1] = {0.0};
    double wi_squared = 0.0;
    
    double avg_profile[n][timestamp+1] = {0.0};
    
    int lattice[n] = {0};
    int particle[m] = {0};
    double height[n] = {0.0};
    

    
    
do{

    gen_lattice_arr(lattice);
    gen_particle_arr(particle);
    init_height(height, lattice);    
    

    for (int j=0; j<=MC; j++)
        {

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
		       
		    

           int dummy = particle[0];         

               if(dummy!=n-1 & dummy!=0)
               {
                    if(lattice[dummy-1]==1 & lattice[dummy]==-1)
                    {

                        double b = dist_u(gen);

                        if( b>0.5)
                        {
                          particle[0] =  dummy + 1; //delr += 1;

                        }

                        else if (b<=0.5)
                        {
                          particle[0] =  dummy - 1; //delr -= 1;
                        }


                    }

                    else if(lattice[dummy-1]==-1 & lattice[dummy]==-1)
                    {
                         particle[0] =  dummy + 1; //delr += 1;
                    }

                    else if(lattice[dummy-1]==1 & lattice[dummy]==1)
                    {
                         particle[0] =  dummy - 1; //delr -= 1;
                    }


               }

               else if(dummy==n-1)
               {
                    if(lattice[dummy-1]==1 & lattice[dummy]==-1)
                    {

                        double b = dist_u(gen);

                        if(b>0.5)
                        {
                          particle[0] =  0; //delr += 1;
                        }
                        else if (b<=0.5)
                        {
                          particle[0] =  dummy - 1; //delr -= 1;
                        }


                    }

                    else if(lattice[dummy-1]==-1 & lattice[dummy]==-1)
                    {
                         particle[0] =  0;  //delr += 1;
                    }

                    else if(lattice[dummy-1]==1 & lattice[dummy]==1)
                    {
                         particle[0] =  dummy - 1;    //delr -= 1;
                    }


               }

               else if(dummy==0)
               {
                   if(lattice[n-1]==1 & lattice[dummy]==-1)
                    {

                        double b = dist_u(gen);

                        if(b>0.5)
                        {
                          particle[0] =  dummy + 1; //delr += 1;
                        }
                        else if (b<=0.5)
                        {
                          particle[0] =  n - 1; //delr -= 1;
                        }


                    }

                    else if(lattice[n-1]==-1 & lattice[dummy]==-1)
                    {
                         particle[0] =  dummy + 1;    //delr += 1;
                    }

                    else if(lattice[n-1]==1 & lattice[dummy]==1)
                    {
                         particle[0] =  n - 1;  //delr -= 1;
                    }


               }
     	  
     	 if (j % 100 == 0)
         {
         	int t = j/100;
         	wi_squared = 0.0;
         	
         	double havg = 0.0;
         	for(int i = 0; i<n; i++)
         	havg += height[i]/(1.0*n);
         	
         	for(int i = 0; i<n; i++)
		   {
		    	wi_squared += pow((havg - height[i]),2);
		   }
		   
		 width_ss[t] += wi_squared;
		
         }
     	  

        }///MC loop



  k++;
 }while(k<ENS);///history loop


	for(int j = 0; j<=timestamp; j++)
	    {
	       	fout<<j*100<<"\t"<<width_ss[j]/(1.0*n*ENS)<<"\n";
	    }

	



gout.close();
fout.close();


return 0;
}
