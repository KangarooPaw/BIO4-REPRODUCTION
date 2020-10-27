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
 26;
 0.95010;-1.34030;-1.08350;,
 0.44790;0.00000;-1.70830;,
 4.43220;0.00000;-1.70830;,
 4.43220;-1.34030;-1.08350;,
 8.85300;0.00000;-1.27260;,
 8.07090;-0.96060;-1.08350;,
 0.95010;1.34030;-1.08350;,
 4.43220;1.34030;-1.08350;,
 8.07090;0.96060;-1.08350;,
 0.44790;1.53060;-0.01990;,
 0.97930;1.33510;1.04450;,
 4.43220;1.33510;1.04450;,
 3.99960;1.73400;-0.01990;,
 8.20820;0.92660;1.04450;,
 8.67110;1.29010;-0.01990;,
 0.44790;0.00000;1.54950;,
 4.43220;0.00000;1.54950;,
 8.72990;0.00000;1.27330;,
 0.97930;-1.33510;1.04450;,
 4.43220;-1.33510;1.04450;,
 8.20820;-0.92660;1.04450;,
 0.44790;-1.53060;-0.01990;,
 3.99960;-1.73400;-0.01990;,
 8.67110;-1.29010;-0.01990;,
 9.56600;0.00000;-0.01990;,
 -0.97650;0.00000;-0.01990;;
 
 24;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;1,6,7,2;,
 4;2,7,8,4;,
 4;9,10,11,12;,
 4;12,11,13,14;,
 4;10,15,16,11;,
 4;11,16,17,13;,
 4;15,18,19,16;,
 4;16,19,20,17;,
 4;18,21,22,19;,
 4;19,22,23,20;,
 4;24,17,20,23;,
 4;14,13,17,24;,
 4;18,15,25,21;,
 4;15,10,9,25;,
 4;6,9,12,7;,
 4;7,12,14,8;,
 4;4,8,14,24;,
 4;5,4,24,23;,
 4;22,3,5,23;,
 4;21,0,3,22;,
 4;25,1,0,21;,
 4;9,6,1,25;;
 
 MeshMaterialList {
  14;
  24;
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6;;
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
    "data/TEXTURE/eye.jpg";
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
  Material {
   0.800000;0.320000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  30;
  -0.260154;-0.732354;-0.629268;,
  0.037364;-0.737291;-0.674541;,
  0.315000;-0.690842;-0.650778;,
  0.000000;0.000000;-1.000000;,
  0.037730;0.000000;-0.999288;,
  0.467597;0.000000;-0.883942;,
  -0.260154;0.732354;-0.629268;,
  0.037364;0.737291;-0.674541;,
  0.315000;0.690842;-0.650778;,
  -0.271695;0.701370;0.658985;,
  0.032654;0.715007;0.698355;,
  0.327931;0.667405;0.668604;,
  -0.427407;0.000000;0.904060;,
  0.026550;0.000000;0.999647;,
  0.475511;0.000000;0.879710;,
  -0.271695;-0.701370;0.658985;,
  0.032654;-0.715006;0.698355;,
  0.327931;-0.667405;0.668604;,
  -0.422798;0.906197;0.006937;,
  0.034928;0.999378;0.004916;,
  0.474055;0.880490;0.003085;,
  0.794380;-0.607418;-0.002004;,
  0.474055;-0.880490;0.003085;,
  0.034928;-0.999378;0.004916;,
  -0.422798;-0.906197;0.006937;,
  -0.683220;-0.522760;0.509836;,
  0.794380;0.607418;-0.002004;,
  -0.683220;0.522760;0.509836;,
  -0.663640;-0.563786;-0.491657;,
  -0.663640;0.563786;-0.491657;;
  24;
  4;0,3,4,1;,
  4;1,4,5,2;,
  4;3,6,7,4;,
  4;4,7,8,5;,
  4;18,9,10,19;,
  4;19,10,11,20;,
  4;9,12,13,10;,
  4;10,13,14,11;,
  4;12,15,16,13;,
  4;13,16,17,14;,
  4;15,24,23,16;,
  4;16,23,22,17;,
  4;21,14,17,22;,
  4;20,11,14,26;,
  4;15,12,25,24;,
  4;12,9,18,27;,
  4;6,18,19,7;,
  4;7,19,20,8;,
  4;5,8,20,26;,
  4;2,5,21,22;,
  4;23,1,2,22;,
  4;24,0,1,23;,
  4;28,28,0,24;,
  4;18,6,29,29;;
 }
 MeshTextureCoords {
  26;
  0.586577;1.106370;,
  0.540815;0.984235;,
  0.903882;0.984235;,
  0.903882;1.106370;,
  1.306725;0.984235;,
  1.235456;1.071770;,
  0.586577;0.862101;,
  0.903882;0.862101;,
  1.235456;0.896701;,
  0.540815;0.844760;,
  0.589238;0.862575;,
  0.903882;0.862575;,
  0.864461;0.826226;,
  1.247968;0.899800;,
  1.290149;0.866676;,
  0.540815;0.984235;,
  0.903882;0.984235;,
  1.295508;0.984235;,
  0.589238;1.105896;,
  0.903882;1.105896;,
  1.247968;1.068671;,
  0.540815;1.123711;,
  0.864461;1.142245;,
  1.290149;1.101795;,
  1.371697;0.984235;,
  0.411017;0.984235;;
 }
}
