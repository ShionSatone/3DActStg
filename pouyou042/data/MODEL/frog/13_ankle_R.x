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
 60;
 2.93540;-8.20460;-8.21140;,
 2.93540;-7.39060;-6.02370;,
 2.93540;-8.52490;-5.19320;,
 2.93540;-9.33880;-7.38090;,
 2.93540;-6.45550;-3.25450;,
 2.93540;-7.49110;-2.49620;,
 1.75890;-3.21220;-0.55650;,
 1.75890;-3.61790;0.12900;,
 0.30510;0.02870;-0.17340;,
 0.30510;0.02870;0.24920;,
 1.46700;-8.20460;-8.21140;,
 1.46700;-7.39060;-6.02370;,
 1.46700;-6.45550;-3.25450;,
 0.87870;-3.21220;-0.55650;,
 0.15180;0.02870;-0.17340;,
 -0.00140;-8.20460;-8.21140;,
 -0.00140;-7.39060;-6.02370;,
 -0.00140;-6.45550;-3.25450;,
 -0.00140;-3.21220;-0.55650;,
 -0.00140;0.02870;-0.17340;,
 -1.46980;-8.20460;-8.21140;,
 -1.46980;-7.39060;-6.02370;,
 -1.46980;-6.45550;-3.25450;,
 -0.88160;-3.21220;-0.55650;,
 -0.15470;0.02870;-0.17340;,
 -2.93820;-8.20460;-8.21140;,
 -2.93820;-7.39060;-6.02370;,
 -2.93820;-6.45550;-3.25450;,
 -1.76170;-3.21220;-0.55650;,
 -0.30800;0.02870;-0.17340;,
 -2.93820;-9.33880;-7.38090;,
 -2.93820;-8.52490;-5.19320;,
 -2.93820;-7.49110;-2.49620;,
 -1.76170;-3.61790;0.12900;,
 -0.30800;0.02870;0.24920;,
 -1.46980;-9.33880;-7.38090;,
 -1.46980;-8.52490;-5.19320;,
 -1.46980;-7.49110;-2.49620;,
 -0.88160;-3.61790;0.12900;,
 -0.15470;0.02870;0.24920;,
 -0.00140;-9.33880;-7.38090;,
 -0.00140;-8.52490;-5.19320;,
 -0.00140;-7.49110;-2.49620;,
 -0.00140;-3.61790;0.12900;,
 -0.00140;0.02870;0.24920;,
 1.46700;-9.33880;-7.38090;,
 1.46700;-8.52490;-5.19320;,
 1.46700;-7.49110;-2.49620;,
 0.87870;-3.61790;0.12900;,
 0.15180;0.02870;0.24920;,
 -1.06460;-9.93660;-11.55780;,
 -1.06460;-9.52600;-11.85840;,
 -0.53300;-9.52600;-11.85840;,
 -0.53300;-9.93660;-11.55780;,
 -0.00140;-9.52600;-11.85840;,
 -0.00140;-9.93660;-11.55780;,
 0.53020;-9.52600;-11.85840;,
 0.53020;-9.93660;-11.55780;,
 1.06180;-9.52600;-11.85840;,
 1.06180;-9.93660;-11.55780;;
 
 58;
 4;0,1,2,3;,
 4;2,1,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;10,11,1,0;,
 4;1,11,12,4;,
 4;4,12,13,6;,
 4;6,13,14,8;,
 4;15,16,11,10;,
 4;11,16,17,12;,
 4;12,17,18,13;,
 4;13,18,19,14;,
 4;20,21,16,15;,
 4;16,21,22,17;,
 4;17,22,23,18;,
 4;18,23,24,19;,
 4;25,26,21,20;,
 4;21,26,27,22;,
 4;22,27,28,23;,
 4;23,28,29,24;,
 4;30,31,26,25;,
 4;26,31,32,27;,
 4;27,32,33,28;,
 4;28,33,34,29;,
 4;35,36,31,30;,
 4;31,36,37,32;,
 4;32,37,38,33;,
 4;33,38,39,34;,
 4;40,41,36,35;,
 4;36,41,42,37;,
 4;37,42,43,38;,
 4;38,43,44,39;,
 4;45,46,41,40;,
 4;41,46,47,42;,
 4;42,47,48,43;,
 4;43,48,49,44;,
 4;3,2,46,45;,
 4;46,2,5,47;,
 4;47,5,7,48;,
 4;48,7,9,49;,
 4;39,24,29,34;,
 4;44,19,24,39;,
 4;49,14,19,44;,
 4;9,8,14,49;,
 4;50,51,52,53;,
 4;53,52,54,55;,
 4;55,54,56,57;,
 4;57,56,58,59;,
 4;57,59,3,45;,
 4;55,57,45,40;,
 4;53,55,40,35;,
 4;50,53,35,30;,
 4;51,50,30,25;,
 4;52,51,25,20;,
 4;54,52,20,15;,
 4;56,54,15,10;,
 4;58,56,10,0;,
 4;59,58,0,3;;
 
 MeshMaterialList {
  1;
  58;
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
    "data\\TEXTURE\\frag.jpg";
   }
  }
 }
 MeshNormals {
  38;
  0.000000;-0.590716;-0.806879;,
  1.000000;0.000000;0.000000;,
  0.991373;0.097562;0.087524;,
  0.946415;0.290775;0.140526;,
  0.916841;0.384929;0.105977;,
  0.000000;-0.590716;-0.806879;,
  0.000000;0.942443;-0.334366;,
  0.000000;0.824607;-0.565706;,
  0.000000;0.394724;-0.918800;,
  0.000000;0.117391;-0.993086;,
  0.000000;0.824607;-0.565706;,
  0.000000;0.394724;-0.918800;,
  0.000000;-0.590716;-0.806879;,
  0.000000;0.394724;-0.918800;,
  0.000000;0.117391;-0.993086;,
  -1.000000;0.000000;0.000000;,
  -0.991373;0.097562;0.087524;,
  -0.946419;0.290764;0.140523;,
  -0.916851;0.384907;0.105971;,
  0.000000;-0.935507;0.353308;,
  0.000000;-0.783457;0.621447;,
  0.000000;-0.309156;0.951011;,
  0.000000;-0.032944;0.999457;,
  0.000000;-0.783457;0.621447;,
  0.972953;-0.136466;-0.186386;,
  0.000000;-0.969120;0.246592;,
  -0.972953;-0.136466;-0.186386;,
  0.000000;0.938716;-0.344692;,
  0.000000;0.117391;-0.993086;,
  0.000000;-0.969119;0.246592;,
  0.000000;-0.032944;0.999457;,
  0.000000;1.000000;0.000000;,
  0.000000;-0.989913;0.141677;,
  0.000000;-0.989913;0.141677;,
  0.000000;-0.989913;0.141677;,
  -0.893274;-0.265550;-0.362690;,
  0.000000;0.940189;-0.340654;,
  0.893274;-0.265550;-0.362690;;
  58;
  4;24,1,1,24;,
  4;1,1,2,2;,
  4;2,2,3,3;,
  4;3,3,4,4;,
  4;27,6,6,27;,
  4;6,6,7,7;,
  4;7,7,8,8;,
  4;8,8,9,28;,
  4;27,6,6,27;,
  4;6,6,10,7;,
  4;7,10,11,8;,
  4;8,11,9,9;,
  4;27,6,6,27;,
  4;6,6,10,10;,
  4;10,10,11,11;,
  4;11,11,9,9;,
  4;27,6,6,27;,
  4;6,6,10,10;,
  4;10,10,13,11;,
  4;11,13,14,9;,
  4;26,15,15,26;,
  4;15,15,16,16;,
  4;16,16,17,17;,
  4;17,17,18,18;,
  4;25,19,19,29;,
  4;19,19,20,20;,
  4;20,20,21,21;,
  4;21,21,22,30;,
  4;25,19,19,25;,
  4;19,19,23,20;,
  4;20,23,21,21;,
  4;21,21,22,22;,
  4;25,19,19,25;,
  4;19,19,20,23;,
  4;23,20,21,21;,
  4;21,21,22,22;,
  4;29,19,19,25;,
  4;19,19,20,20;,
  4;20,20,21,21;,
  4;21,21,22,22;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;0,0,12,12;,
  4;12,12,5,5;,
  4;5,5,5,5;,
  4;5,5,0,0;,
  4;32,33,29,25;,
  4;34,32,25,25;,
  4;34,34,25,25;,
  4;33,34,25,29;,
  4;35,35,26,26;,
  4;36,36,27,27;,
  4;36,36,27,27;,
  4;36,36,27,27;,
  4;36,36,27,27;,
  4;37,37,24,24;;
 }
 MeshTextureCoords {
  60;
  0.968726;0.677042;,
  0.968726;0.659588;,
  0.968726;0.683910;,
  0.968726;0.701363;,
  0.968726;0.639537;,
  0.968726;0.661744;,
  0.964338;0.569993;,
  0.964338;0.578692;,
  0.958916;0.500500;,
  0.958916;0.500500;,
  0.963249;0.677042;,
  0.963249;0.659588;,
  0.963249;0.639537;,
  0.961055;0.569993;,
  0.958344;0.500500;,
  0.957772;0.677042;,
  0.957772;0.659588;,
  0.957772;0.639537;,
  0.957772;0.569993;,
  0.957772;0.500500;,
  0.952296;0.677042;,
  0.952296;0.659588;,
  0.952296;0.639537;,
  0.954490;0.569993;,
  0.957201;0.500500;,
  0.946819;0.677042;,
  0.946819;0.659588;,
  0.946819;0.639537;,
  0.951207;0.569993;,
  0.956629;0.500500;,
  0.946819;0.701363;,
  0.946819;0.683910;,
  0.946819;0.661744;,
  0.951207;0.578692;,
  0.956629;0.500500;,
  0.952296;0.701363;,
  0.952296;0.683910;,
  0.952296;0.661744;,
  0.954490;0.578692;,
  0.957201;0.500500;,
  0.957772;0.701363;,
  0.957772;0.683910;,
  0.957772;0.661744;,
  0.957772;0.578692;,
  0.957772;0.500500;,
  0.963249;0.701363;,
  0.963249;0.683910;,
  0.963249;0.661744;,
  0.961055;0.578692;,
  0.958344;0.500500;,
  0.953807;0.714181;,
  0.953807;0.705377;,
  0.955790;0.705377;,
  0.955790;0.714181;,
  0.957772;0.705377;,
  0.957772;0.714181;,
  0.959755;0.705377;,
  0.959755;0.714181;,
  0.961738;0.705377;,
  0.961738;0.714181;;
 }
}