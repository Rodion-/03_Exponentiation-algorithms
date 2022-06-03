#include <iostream>
#include <filesystem>
#include <fstream>
#include <memory>
#include <vector>


enum class TYPE_EX
{
	EX1 = 1,
	EX2 , 
	EX3
};

class ITests
{
	public:
	virtual double run ( double num  , int exp  , TYPE_EX EX ){}
	
};

class Power : public ITests
{
	double pow = 0;
	
	double power1 ( double num  , int exp  )
	{
		double pow = 1;
		
		if( exp == 0 ) return 1;	
			
		for( int i = 0 ; i < exp; i++ )
		{
		 	pow *= num;
		}
		
		return pow;
	}
	
	double power2 ( double num  , int exp  )
	{			
		int n = exp;
		int delta = n;
			
		if( exp == 0 ) return 1;	
			
		double x = num * num;
			
		//1.найти ближайшую степень двойки к заданной степене 
		int temp = 0;
		while( n > 1 )
		{
			n /= 2;
			
			temp++;
		}
			
		int two = 1;
		//2.получить два в степени temp
		for( int i = 0 ; i < temp; i++ )
		{
			two *= 2;			
		}
		
		//3.определить число недостающих степеней
		delta -= two;
		
		//4.получить ближайшую степень числа
		for( int i = 0; i < temp-1; i++ )
		{
			x *= x;
		}
		//5.домножить на недостающую степень
		for( int i = 0 ; i < delta; i++ )
		{
			x *= num;
		} 	
		
		return x;		 		
	}
	
	double power3 ( double num  , int exp  )
	{
		if( exp == 0 ) return 1;	
		
		int n = exp;
			
		double d = num;
			
		double p = 1;
			
		while( n > 1 )
		{
			n /= 2;
		
			d *= d;
				
			if( n % 2 == 1 )	
			{
				p *= d;
			}					
		}	
		//p *= d;
		
		return p;	
	}
	
	
	public:
	
	double run ( double num  , int exp  , TYPE_EX EX ) override
	{
		switch( EX )
		{
			case TYPE_EX::EX1 : pow = power1( num , exp ); break;
			
			case TYPE_EX::EX2 : pow = power2( num , exp ); break;
			
			case TYPE_EX::EX3 : pow = power3( num , exp ); break;
			
			default: break;		
		}
		
		return pow;
	}	
	
	
	
	
	
};

class Tester
{
	std::string file1_name;
	std::string file2_name;
	
	std::string path;
	
	std::unique_ptr< ITests > itests;
	
	public:
	
	Tester( const std::string& _path , std::unique_ptr< ITests > _itests ) : path( _path ) , itests( std::move( _itests ) ) {}
	~Tester(){}
	
	void RunTests(  TYPE_EX EX )
	{
		int n = 0;
		
		while( true )
		{
			file1_name = path + (std::string)"test." + std::to_string( n ) + (std::string)".in";
			file2_name = path + (std::string)"test." + std::to_string( n ) + (std::string)".out";
			
			
			
			if( !std::filesystem::exists( (std::filesystem::path) file1_name ) || !std::filesystem::exists( (std::filesystem::path) file2_name ) )
			{
				std::cout<<"file not exists!"<<std::endl;
				break;
			}	
			
			RunTest( file1_name , file2_name , EX );
			
			n++;
		}
	}
	
	bool RunTest ( const std::string& file1_name , const std::string& file2_name , TYPE_EX EX )
	{
		std::ifstream f_initial_data( file1_name , std::ios::binary );
		std::ifstream f_result( file2_name , std::ios::binary );
	
		
		using string_pool = std::vector<std::string>;
		
		string_pool vstr;
		
		vstr.reserve(10);
		std::string line;
		
		
		
		
		while( getline( f_initial_data , line ) )
		{
			vstr.push_back( line );
			line.clear();
			
		}
		
		long exp = 0;
		double num = 0;
		double expect = 0;
		
		if( vstr.size() > 1 ) 
		{
			exp = std::stod( vstr.back() );
			vstr.pop_back();
			num = std::stod( vstr.back() );
			vstr.pop_back();
			
			
			std::cout<<" num = "<< num << std::endl;
			std::cout<<" exp = "<< exp << std::endl;		
		}

		vstr.clear();
		
		while( getline( f_result , line ) )
		{
			vstr.push_back( line );
			line.clear();		
		}
		
		
		if( vstr.size() > 0 )
		{
			std::cout<<" result string = " << vstr.back() << std::endl;
			expect = std::stod( vstr.back() );
		
			std::cout<<" expect = " << std::setprecision(11) << expect << std::endl;
		}
		

		double actual = itests->run( num , exp , EX );
		
						
		expect == actual ? std::cout << " true" << " expect = " << expect << " actual " << actual   : std::cout << " false" << " expect = " << expect << " actual " << actual  ;
		
		std::cout << std::endl;
	
		f_initial_data.close();
		f_result.close();
		
		return actual == expect;
	}
};

int main ( int argc , char** argv )
{
	std::cout<<"algo3"<<std::endl;
	
	try
	{
    
    
		#define EXP1 1
		#if EXP1
		{
			std::cout<<"--------------EXAMPLE1--------------"<<std::endl;
			
			Tester test( "" , std::make_unique<Power> ( ) );		
			
			test.RunTests( TYPE_EX::EX1 );		
		}
		#endif
		
		#define EXP2 1
		#if EXP2
		{
			std::cout<<"--------------EXAMPLE2--------------"<<std::endl;
			
			Tester test( "" , std::make_unique<Power> ( ) );		
			
			test.RunTests( TYPE_EX::EX2 );
		}
		#endif
		
		
		#define EXP3 1
		#if EXP3
		{
			std::cout<<"--------------EXAMPLE3--------------"<<std::endl;
			
			Tester test( "" , std::make_unique<Power> ( ) );		
			
			test.RunTests( TYPE_EX::EX3 );
		}
		#endif		
	}
	catch( ... )
	{
		std::cout<<"error"<<std::endl;
	}
	
	

	return 0;
}
