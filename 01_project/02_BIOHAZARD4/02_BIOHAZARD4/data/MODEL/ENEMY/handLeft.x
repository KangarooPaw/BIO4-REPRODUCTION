xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 38;
 -0.58700;-0.50420;-0.65350;,
 -2.01370;-1.00640;-1.08440;,
 -2.01370;-0.26910;-1.44630;,
 -0.39890;0.00000;-1.01590;,
 -2.70740;-1.00300;-1.50830;,
 -3.54860;-0.84750;-1.98210;,
 -4.06890;-0.05040;-2.00200;,
 -2.70740;-0.32550;-1.87010;,
 -2.57140;1.17010;-1.33090;,
 -0.43280;0.52900;-0.90250;,
 -4.11490;0.08830;-1.22920;,
 -3.91600;1.74000;-1.06470;,
 -0.08330;0.82420;0.01790;,
 -2.57140;1.34700;0.01780;,
 -2.57140;1.17010;1.36770;,
 -0.43280;0.52900;0.93930;,
 -3.91600;1.98370;-0.16820;,
 -3.91600;1.71000;1.39400;,
 -2.01370;0.00000;1.48310;,
 -0.39890;0.00000;1.05160;,
 -4.83750;0.68210;1.48310;,
 -2.01370;-0.57860;1.12120;,
 -0.58700;-0.50420;0.69030;,
 -3.02670;-0.07750;1.27570;,
 -2.01370;-0.56910;0.01780;,
 -0.77270;-0.48120;0.01790;,
 -3.70450;-0.71950;-0.90690;,
 -5.17260;-0.20840;-0.57200;,
 -3.91040;-1.12450;-0.81620;,
 -3.73380;-1.13270;0.86330;,
 -5.21000;-0.20840;1.29400;,
 -5.11830;0.50980;-0.68970;,
 0.49590;0.00000;0.01790;,
 -3.59460;-0.76870;-1.20940;,
 -4.37440;-0.45260;-1.18000;,
 -4.59700;-0.11260;-1.19980;,
 -4.55110;-0.25130;-1.62370;,
 -4.32840;-0.53140;-1.60390;;
 
 36;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;3,2,8,9;,
 4;2,10,11,8;,
 4;12,13,14,15;,
 4;13,16,17,14;,
 4;15,14,18,19;,
 4;14,17,20,18;,
 4;19,18,21,22;,
 4;18,20,23,21;,
 4;22,21,24,25;,
 4;21,23,26,24;,
 4;27,28,29,30;,
 4;16,31,20,17;,
 4;22,25,32,19;,
 4;19,32,12,15;,
 4;9,8,13,12;,
 4;8,11,16,13;,
 4;10,31,16,11;,
 4;33,26,31,10;,
 4;24,26,33,1;,
 4;25,24,1,0;,
 4;32,25,0,3;,
 4;12,32,3,9;,
 4;1,33,5,4;,
 4;34,35,36,37;,
 4;10,2,7,6;,
 4;2,1,4,7;,
 4;33,10,35,34;,
 4;10,6,36,35;,
 4;6,5,37,36;,
 4;5,33,34,37;,
 4;31,26,28,27;,
 4;26,23,29,28;,
 4;23,20,30,29;,
 4;20,31,27,30;;
 
 MeshMaterialList {
  13;
  36;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.793600;0.787200;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/zombieskin.png";
   }
  }
  Material {
   0.523922;0.473726;0.257255;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.577255;0.577255;0.087843;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.169412;0.169412;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/zombieskin.png";
   }
  }
  Material {
   0.545882;0.389020;0.235294;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/\eye.jpg";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.771765;0.759216;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/met.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/beruto.png";
   }
  }
  Material {
   0.072000;0.024000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.064000;0.072000;0.040000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.545600;0.388800;0.235200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/eye.jpg";
   }
  }
  Material {
   0.800000;0.771765;0.759216;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/hukufrontenemy.png";
   }
  }
  Material {
   0.800000;0.771765;0.759216;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/hukubackenemy.png";
   }
  }
 }
 MeshNormals {
  60;
  0.458880;-0.715623;-0.526605;,
  0.420427;-0.461346;-0.781281;,
  -0.462311;-0.884800;-0.058285;,
  0.502546;0.011404;-0.864475;,
  0.257067;-0.175243;-0.950372;,
  -0.591475;-0.003347;-0.806316;,
  0.521951;0.293002;-0.801072;,
  0.055601;0.139125;-0.988713;,
  -0.417284;0.286833;-0.862323;,
  0.551257;0.709395;0.439176;,
  0.321372;0.926961;0.193553;,
  0.388446;0.910887;0.139262;,
  0.477793;0.002091;0.878470;,
  0.107068;-0.218044;0.970048;,
  -0.024743;-0.259924;0.965312;,
  0.299582;-0.883356;0.360463;,
  -0.030988;-0.866347;0.498481;,
  -0.141181;-0.668912;0.729812;,
  0.613477;0.789713;-0.000077;,
  0.332671;0.942988;-0.010145;,
  0.402251;0.915313;-0.019927;,
  -0.861311;0.476595;-0.176071;,
  -0.401579;-0.915795;-0.007293;,
  -0.029562;-0.986270;0.162472;,
  0.332998;-0.941196;0.057117;,
  0.530399;-0.847748;0.000174;,
  0.377187;-0.305820;-0.874188;,
  -0.126294;-0.321076;-0.938595;,
  -0.608920;-0.788719;0.084488;,
  -0.810838;-0.582318;0.058720;,
  -0.730985;-0.546353;-0.408851;,
  -0.637452;-0.732170;-0.239963;,
  -0.556591;-0.830464;0.023148;,
  0.252554;0.215030;0.943387;,
  0.144192;0.149191;0.978239;,
  0.033336;0.080773;0.996175;,
  -0.757767;0.588948;-0.280942;,
  -0.892460;0.446853;0.061951;,
  -0.759434;0.645054;0.084651;,
  0.518296;-0.828044;0.213806;,
  0.752489;0.356523;0.553762;,
  0.251834;0.935828;-0.246589;,
  0.330040;0.919530;-0.213397;,
  0.405777;0.896350;-0.178607;,
  -0.535533;-0.357386;-0.765166;,
  -0.084060;-0.960703;0.264542;,
  -0.032272;-0.972438;0.230919;,
  0.184958;-0.951666;0.245198;,
  0.518012;-0.828309;-0.213467;,
  0.752219;0.357069;-0.553777;,
  -0.277211;-0.950716;0.138901;,
  -0.196391;-0.965046;0.173542;,
  -0.142858;0.954163;-0.262992;,
  0.168550;0.954476;-0.246104;,
  0.045480;0.068830;0.996591;,
  -0.440372;0.861048;-0.254301;,
  -0.258040;-0.112442;-0.959569;,
  0.862271;-0.496163;-0.101542;,
  0.025979;-0.299987;0.953590;,
  -0.974174;0.222959;0.035690;;
  36;
  4;0,1,4,3;,
  4;26,27,27,26;,
  4;3,4,7,6;,
  4;4,5,8,7;,
  4;18,19,10,9;,
  4;19,20,11,10;,
  4;33,34,13,12;,
  4;34,35,14,13;,
  4;12,13,16,15;,
  4;13,14,17,16;,
  4;15,16,23,24;,
  4;16,17,22,23;,
  4;32,32,32,32;,
  4;36,21,37,38;,
  4;15,24,25,39;,
  4;12,40,18,9;,
  4;41,42,19,18;,
  4;42,43,20,19;,
  4;5,21,36,8;,
  4;2,22,44,5;,
  4;23,22,45,46;,
  4;24,23,46,47;,
  4;25,24,0,48;,
  4;18,49,3,6;,
  4;46,2,50,51;,
  4;28,29,30,31;,
  4;52,53,53,52;,
  4;4,1,26,26;,
  4;54,54,54,54;,
  4;52,52,55,55;,
  4;27,27,31,30;,
  4;50,2,28,31;,
  4;44,56,56,56;,
  4;57,57,57,57;,
  4;17,14,58,58;,
  4;37,21,59,59;;
 }
 MeshTextureCoords {
  38;
  0.320559;0.931801;,
  0.108630;1.003483;,
  0.108630;0.898244;,
  0.348500;0.859834;,
  0.005585;1.002997;,
  -0.119370;0.980802;,
  -0.196658;0.867028;,
  0.005585;0.906295;,
  0.025787;0.692820;,
  0.343464;0.784328;,
  -0.203491;0.847231;,
  -0.173945;0.611476;,
  0.395380;0.742192;,
  0.025787;0.667571;,
  0.025787;0.692820;,
  0.343464;0.784328;,
  -0.173945;0.576691;,
  -0.173945;0.615758;,
  0.108630;0.859834;,
  0.348500;0.859834;,
  -0.310829;0.762475;,
  0.108630;0.942421;,
  0.320559;0.931801;,
  -0.041845;0.870896;,
  0.108630;0.941065;,
  0.292974;0.928518;,
  -0.142528;0.962532;,
  -0.360606;0.889580;,
  -0.173113;1.020340;,
  -0.146881;1.021510;,
  -0.366162;0.889580;,
  -0.352540;0.787068;,
  0.481417;0.859834;,
  -0.126203;0.969555;,
  -0.242038;0.924436;,
  -0.275104;0.875906;,
  -0.268286;0.895704;,
  -0.235205;0.935684;;
 }
}
