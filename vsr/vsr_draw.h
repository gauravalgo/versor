/*
	
	Pablo Colapinto
	VSR2.0

*/

#ifndef VSR_DRAW_H_INCLUDED
#define VSR_DRAW_H_INCLUDED  

#include "gfx/gfx_glyphs.h" 


namespace vsr{
	
	
	template<class A>
	void Draw( const A& s, float r = 1, float g = 1, float b = 1, float a = 1){
		glPushMatrix(); 
		glNormal3f(0,0,1);
		glColor4f(r,g,b,a);
			Immediate(s);
		glPopMatrix();
	} 
	
           
	// FEATURE ExTRAcTION (ROTATION AND POSITION)

	Rot AA( const Vec& s){
		//Biv b = Ro::dir( s ).copy<Biv>();               
        Rot r = Gen::ratio(Vec::z, s.unit() ); 
        return Gen::aa(r);
    }                    

	Rot AA( const Dlp& s){
		//Biv b = Ro::dir( s ).copy<Biv>();               
        Rot r = Gen::ratio(Vec::z, Vec(s).unit() ); 
        return Gen::aa(r);
    }  
	Vec Pos( const Dlp& s){ 
		return Fl::locd( s , Ori(1));// true );   
	    
		//return Vec(s) * s[3];
	}   
	
	Rot AA( const Cir& s){
		Biv b = Ro::dir( s ).copy<Biv>();               
        Rot r = Gen::ratio(Vec::z, Op::dle( b ).unit() ); 
        return Gen::aa(r);
    }  
	Pnt Pos( const Cir& s){
		return Ro::loc( s );
	}          
	
	// 
	void Immediate (const Vec& s){
	    gfx::Glyph::Line(s);
		glPushMatrix();	
			gfx::GL::translate( s.begin() );
			gfx::GL::rotate( AA(s).begin() );	
			Glyph::Cone();
		glPopMatrix();
	}                         
	
	void Immediate (const Dlp& s){
	    gfx::GL::translate( Pos(s).begin() );
		gfx::GL::rotate( AA(s).begin() ); 
	    Glyph::SolidGrid();
	}

    void Immediate( const Cir& s )	{  
		VT rad = Ro::rad( s );
	    bool im = Ro::size(s, false) > 0 ? 1 : 0;  
		 
		//AA(s).vprint();
		gfx::GL::translate( Pos(s).begin() );
		gfx::GL::rotate( AA(s).begin() ); 

			im ? gfx::Glyph::Circle( rad ) :  gfx::Glyph::DashedCircle( rad );            
	}  
	
	void Immediate (const Pnt& s){
 
	    VT ta = Ro::size( s, true );

	    //Draw as dual Sphere (if |radius^2| > 0.000001);
	    if ( fabs(ta) >  FPERROR ) {
		   // printf("spehere!!!!!!!!!!!!!!!!!!!!\n");
	        bool real = ta > 0 ? 1 : 0;	

	        Pnt p = Ro::cen( s );
	        VT t = sqrt ( fabs ( ta ) );

	        gfx::GL::translate ( p.begin() );
	        (real) ? gfx::Glyph::SolidSphere(t, 5+ floor(t*30), 5+floor(t*30)) : Glyph::Sphere(t);	
	    } else {  
		   // printf("NOOOOOO\n");
	        gfx::Glyph::Point(s);
	    }
	}
	
     void Immediate (const Par& s){
	        //Is Imaginary?
	        double size = Ro::size( s, false );
	        std::vector<Pnt> pp = Ro::split( s );

	        double ta = Ro::size( pp[0], true );   
	
			pp[0].vprint(); pp[1].vprint();

	        if ( fabs(ta) >  FPERROR ) {				
	            Pnt p1 = Ro::cen( pp[0] );
	            Pnt p2 = Ro::cen( pp[1] );
	            double t = sqrt ( fabs ( ta ) );
	            bool real = size > 0 ? 1 : 0;	

	            glPushMatrix();
	            gfx::GL::translate ( p1.begin() );//(p1[0], p1[1], p1[2]);
	            (real) ? gfx::Glyph::SolidSphere(t, 5+ floor(t*30), 5+floor(t*30)) : gfx::Glyph::Sphere(t);	
	            glPopMatrix();

	            gfx::GL::translate ( p2.begin() );
	            (real) ? gfx::Glyph::SolidSphere(t, 5+ floor(t*30), 5+floor(t*30)) : gfx::Glyph::Sphere(t);	

	        } else {
	            gfx::Glyph::Point(pp[0]);
	            gfx::Glyph::Point(pp[1]);
	        }
	}  
	
	void Immediate (const Dll& s){
	    Drv d = Fl::dir( s.undual() );
	    Dls v = Fl::loc( s , PAO, true);
	    gfx::GL::translate (v.begin());
	    gfx::Glyph::DashedLine(d * 10, d * -10);	
	}
}


#endif