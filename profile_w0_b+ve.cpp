/***Prachi Bisht. Program created on 28/10/2018 ***/
/*** Surface profile when w=0 */
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <random>

#define n 256
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


void init_height(double *height, int *lattice)
{
	height[0] = 0;
	for (int i = 1; i<n; i++)
	   height[i] = height[i-1] + lattice[i-1];
}




int main()
{
    std::ofstream fout, hout, gout, kout, lout;

    int MC = 5000, ENS = 1000, r =0, delr = 0, dummy = 0, k = 0, current = 0, counter = 0;
    double beta = 1.0, J = 0;
    fout.open("1p_profile256_w0_b1.0_t5000flat.dat", std::ios::out);

    int lattice[n] = {0};
    int particle[m] = {0};
    double height[n] = {0.0};

    double bias = 0.5;
    int h = n/2;

    double profile_ss[n] = {0.0};
do{

    gen_lattice_arr(lattice);
    gen_particle_arr(particle);
    init_height(height, lattice);


    for (int j=0; j<MC; j++)
        {

          for (int i=0; i<n; i++)
          {

           //begin surface update///

	    int r = dist_n(gen);
	    int x = search_sites(particle, (r+1));
	    
	    if (r==n-1) x = search_sites(particle, 0);
	    
            if (x>0)
            {
	       
               if(lattice[r]==1)
               {

                       if(r!=n-1 && lattice[r+1]==-1)
                       {
                           
		                   double p = 1/(1 + exp(-2*beta*x));
		                   double s = dist_u(gen);
		                   if(s < p)
		                   {
		                       lattice[r]*=-1;
		                       lattice[r+1]*=-1;
		                       height[r+1] -= 2;
//		                       current -= 1;


		                   }

                           
                       }

                       else if(r==n-1 && lattice[0]==-1)
                       {
                           
		                   double p = 1/(1 + exp(-2*beta*x));
		                   double s = dist_u(gen);
		                   if(s < p)
		                   {
		                       lattice[r]*=-1;
		                       lattice[0]*=-1;
		                       //counter -= 2;
		                        height[0] -= 2;
//		                       current -= 1;
		                   }		           


                       }

               }

               else if(lattice[r]==-1)
               {

                       if(r!=n-1 && lattice[r+1]==1)
                       {
                                double p = 1*exp(-2*beta*x)/(1 + exp(-2*beta*x));
		                   double s = dist_u(gen);
		                   if(s < p)
		                   {
		                       lattice[r]*=-1;
		                       lattice[r+1]*=-1;
		                       height[r+1] += 2;
//		                       current += 1;

		                   }
                       }

                       else if(r==n-1 && lattice[0]==1)
                       {
                           
		                   double p = 1*exp(-2*beta*x)/(1 + exp(-2*beta*x));
		                   double s = dist_u(gen);
		                   if(s < p)
		                   {
		                       lattice[r]*=-1;
		                       lattice[0]*=-1;
//		                       counter += 2;
		                       height[0] += 2;
//		                       current += 1;
		                   }
		           
                       }


               }
               
            }
            
          


	   ///begin particle update///
           int dummy = particle[0];
	   int s = dist_n(gen);
	   if (dummy == s)
	   {
            
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

//                    else if(lattice[dummy-1]==-1 & lattice[dummy]==1)
//                    {

//                        double b = dist_u(gen);

//                        if( b>0.5)
//                        {
//                          particle[0] =  dummy + 1;

//                        }

//                        else if (b<=0.5)
//                        {
//                          particle[0] =  dummy - 1;
//                        }


//                    }


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

//                    else if(lattice[dummy-1]==-1 & lattice[dummy]==1)
//                    {

//                        double b = dist_u(gen);

//                        if(b>0.5)
//                        {
//                          particle[0] =  0;
//                        }
//                        else if (b<=0.5)
//                        {
//                          particle[0] =  dummy - 1;
//                        }


//                    }


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

//                    else if(lattice[n-1]==-1 & lattice[dummy]==1)
//                    {

//                        double b = dist_u(gen);

//                        if(b>0.5)
//                        {
//                          particle[0] =  dummy + 1;
//                        }
//                        else if (b<=0.5)
//                        {
//                          particle[0] =  n - 1;
//                        }


//                    }
               
            }


	}

     }///microstep loop


    }///MC loop

	for(int i = 0; i<n; i++)
           {
		          profile_ss[i] += height[i];
           }


  k++;
 }while(k<ENS);///history loop




	for (int i = 0; i<n; i++)
		fout<<i<<"\t"<<profile_ss[i]/(1.0*ENS)<<"\n";



gout.close();
fout.close();


return 0;
}
