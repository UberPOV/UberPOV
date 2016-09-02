// This work is licensed under the Creative Commons Attribution 3.0 Unported License.
// To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/
// or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View,
// California, 94041, USA.
//
// UberPOV Raytracer sample file.
// Created by Christoph Lipka - 2013-08-23
// Updated by Christoph Lipka - 2016-08-24
// This file demonstrates the stochastic anti-aliasing mode.
//
// +w800 +h600 -a
// +w800 +h600 +am2 +a0.1
// +w800 +h600 +am3 +a0.1  +ac0.9  +r3
// +w800 +h600 +am3 +a0.03 +ac0.99 +r6

#version unofficial patch 3.7;
#patch "upov-minnaert" 0.9;

// also toy around with this:
#declare Focal_Blur = no;

global_settings {
  assumed_gamma 1.0
}

camera {
  perspective angle 20
  location  <0.0, 30,-1.0>
  right     x*image_width/image_height
  look_at   <0.0, 1.5, 0>
  #if (Focal_Blur)
    focal_point <0.0, 1.0, -0.5>
    blur_samples 1, 64
    aperture 0.1
    confidence 0.9
    variance   0.1
  #end
}

light_source {
  vnormalize(<-1,1,1>)*10000 color rgb <0.6,0.5,0.3>
  area_light x*500,y*500, 9,9 adaptive 1 circular orient
}

light_source {
  vnormalize(<0,1,0>)*10000 color rgb <0.4,0.5,0.7>
  area_light x*500,y*500, 9,9 adaptive 1 circular orient
}

sky_sphere {
  pigment {
    gradient <0,1,0>
    color_map {
      [0.00 rgb <0.6,0.7,1.0>]
      [0.35 rgb <0.1,0.0,0.8>]
      [0.65 rgb <0.1,0.0,0.8>]
      [1.00 rgb <0.6,0.7,1.0>] 
    } 
    scale 2
  }
}

plane{ <0,1,0>, 0 
  texture{
    pigment{ color rgb 0.5 }
    finish {
      ambient 0.1
      diffuse 0.9
      phong 0.1
    }
  }
}


// Far Left: Brilliance

sphere { <-3.75,1,2.5>, 1
  texture {
    pigment { rgb <1.0, 0.7, 0.2> }
    finish {
      ambient 0.1
      diffuse albedo 0.7
      brilliance 0.7
    }
  }
  interior { ior 1.5 }
}

sphere { <-3.75,1,0>, 1
  texture {
    pigment { rgb <1.0, 0.7, 0.2> }
    finish {
      ambient 0.1
      diffuse albedo 0.7
      brilliance 1.0
    }
  }
  interior { ior 1.5 }
}

sphere { <-3.75,1,-2.5>, 1
  texture {
    pigment { rgb <1.0, 0.7, 0.2> }
    finish {
      ambient 0.1
      diffuse albedo 0.7
      brilliance 1.4
    }
  }
  interior { ior 1.5 }
}


// Middle Left: Lommel-Seeliger

sphere { <-1.25,1,2.5>, 1
  texture {
    pigment { rgb <1.0, 0.7, 0.2> }
    finish {
      ambient 0.1
      diffuse albedo 0.7
      lommel_seeliger 1.0
    }
  }
  interior { ior 1.5 }
}

sphere { <-1.25,1,0>, 1
  texture {
    pigment { rgb <1.0, 0.7, 0.2> }
    finish {
      ambient 0.1
      diffuse albedo 0.7
      lommel_seeliger 0.0
    }
  }
  interior { ior 1.5 }
}


// Middle Right: Minnaert

sphere { <1.25,1,2.5>, 1
  texture {
    pigment { rgb <1.0, 0.7, 0.2> }
    finish {
      ambient 0.1
      diffuse albedo 0.7
      minnaert 0.7
    }
  }
  interior { ior 1.5 }
}

sphere { <1.25,1,0>, 1
  texture {
    pigment { rgb <1.0, 0.7, 0.2> }
    finish {
      ambient 0.1
      diffuse albedo 0.7
      minnaert 1.0
    }
  }
  interior { ior 1.5 }
}

sphere { <1.25,1,-2.5>, 1
  texture {
    pigment { rgb <1.0, 0.7, 0.2> }
    finish {
      ambient 0.1
      diffuse albedo 0.7
      minnaert 1.4
    }
  }
  interior { ior 1.5 }
}


// Far Right: Oren-Nayar

sphere { <3.75,1,2.5>, 1
  texture {
    pigment { rgb <1.0, 0.7, 0.2> }
    finish {
      ambient 0.1
      diffuse albedo 0.7
      oren_nayar 1
    }
  }
  interior { ior 1.5 }
}

sphere { <3.75,1,0>, 1
  texture {
    pigment { rgb <1.0, 0.7, 0.2> }
    finish {
      ambient 0.1
      diffuse albedo 0.7
      oren_nayar 0
    }
  }
  interior { ior 1.5 }
}
