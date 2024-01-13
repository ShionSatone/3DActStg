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
 36;
 -12.05461;-2.29495;2.40605;,
 0.13637;-1.57327;1.68599;,
 0.13637;0.11272;2.38435;,
 -12.05461;0.11109;3.40267;,
 0.13637;1.79871;1.68599;,
 -12.05461;2.51714;2.40605;,
 0.13637;2.49707;0.00000;,
 -12.05461;3.51376;0.00000;,
 0.13637;1.79871;-1.68599;,
 -12.05461;2.51714;-2.40605;,
 0.13637;0.11272;-2.38435;,
 -12.05461;0.11109;-3.40267;,
 0.13637;-1.57328;-1.68599;,
 -12.05461;-2.29495;-2.40605;,
 0.13637;-2.27163;-0.00000;,
 -12.05461;-3.29158;0.00000;,
 0.13637;-1.57327;1.68599;,
 -12.05461;-2.29495;2.40605;,
 -12.05461;0.11109;3.40267;,
 -13.93490;0.11273;0.00000;,
 -12.05461;-2.29495;2.40605;,
 -12.05461;2.51714;2.40605;,
 -12.05461;3.51376;0.00000;,
 -12.05461;2.51714;-2.40605;,
 -12.05461;0.11109;-3.40267;,
 -12.05461;-2.29495;-2.40605;,
 -12.05461;-3.29158;0.00000;,
 0.13637;-1.57327;1.68599;,
 1.72715;0.11272;0.00000;,
 0.13637;0.11272;2.38435;,
 0.13637;1.79871;1.68599;,
 0.13637;2.49707;0.00000;,
 0.13637;1.79871;-1.68599;,
 0.13637;0.11272;-2.38435;,
 0.13637;-1.57328;-1.68599;,
 0.13637;-2.27163;-0.00000;;
 
 24;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,16,17;,
 3;18,19,20;,
 3;21,19,18;,
 3;22,19,21;,
 3;23,19,22;,
 3;24,19,23;,
 3;25,19,24;,
 3;26,19,25;,
 3;20,19,26;,
 3;27,28,29;,
 3;29,28,30;,
 3;30,28,31;,
 3;31,28,32;,
 3;32,28,33;,
 3;33,28,34;,
 3;34,28,35;,
 3;35,28,27;;
 
 MeshMaterialList {
  1;
  24;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\witch.jpg";
   }
  }
 }
 MeshNormals {
  26;
  0.083334;-0.704646;0.704648;,
  0.083241;0.000001;0.996529;,
  0.083147;0.704659;0.704657;,
  0.083108;0.996541;0.000000;,
  0.083147;0.704659;-0.704657;,
  0.083241;0.000002;-0.996530;,
  0.083334;-0.704647;-0.704648;,
  0.083372;-0.996518;0.000001;,
  0.519014;-0.604410;0.604411;,
  0.518975;0.000001;0.854789;,
  0.518937;0.604444;0.604443;,
  0.518921;0.854822;0.000000;,
  0.518937;0.604444;-0.604443;,
  0.518975;0.000001;-0.854789;,
  0.519014;-0.604410;-0.604410;,
  0.519030;-0.854756;0.000002;,
  -1.000000;0.000115;-0.000000;,
  1.000000;0.000000;0.000000;,
  -0.875256;0.000029;0.483660;,
  -0.875325;-0.341896;0.341926;,
  -0.875186;0.342103;0.342074;,
  -0.875157;0.483839;0.000000;,
  -0.875186;0.342103;-0.342074;,
  -0.875256;0.000029;-0.483660;,
  -0.875325;-0.341896;-0.341926;,
  -0.875355;-0.483481;0.000000;;
  24;
  4;0,8,9,1;,
  4;1,9,10,2;,
  4;2,10,11,3;,
  4;3,11,12,4;,
  4;4,12,13,5;,
  4;5,13,14,6;,
  4;6,14,15,7;,
  4;7,15,8,0;,
  3;18,16,19;,
  3;20,16,18;,
  3;21,16,20;,
  3;22,16,21;,
  3;23,16,22;,
  3;24,16,23;,
  3;25,16,24;,
  3;19,16,25;,
  3;8,17,9;,
  3;9,17,10;,
  3;10,17,11;,
  3;11,17,12;,
  3;12,17,13;,
  3;13,17,14;,
  3;14,17,15;,
  3;15,17,8;;
 }
 MeshTextureCoords {
  36;
  0.277960;0.712340;,
  0.277960;0.656140;,
  0.282640;0.656140;,
  0.282640;0.712340;,
  0.287310;0.656140;,
  0.287310;0.712340;,
  0.291980;0.656140;,
  0.291980;0.712340;,
  0.296650;0.656140;,
  0.296650;0.712340;,
  0.301320;0.656140;,
  0.301320;0.712340;,
  0.305990;0.656140;,
  0.305990;0.712340;,
  0.310670;0.656140;,
  0.310670;0.712340;,
  0.315340;0.656140;,
  0.315340;0.712340;,
  0.395350;0.801800;,
  0.395350;0.767810;,
  0.420390;0.791430;,
  0.370310;0.791430;,
  0.359940;0.766390;,
  0.370310;0.741350;,
  0.395350;0.730980;,
  0.420390;0.741350;,
  0.430760;0.766390;,
  0.436280;0.562890;,
  0.411890;0.588670;,
  0.411890;0.552790;,
  0.387490;0.562890;,
  0.377390;0.587290;,
  0.387490;0.611680;,
  0.411890;0.621780;,
  0.436280;0.611680;,
  0.446380;0.587290;;
 }
}
