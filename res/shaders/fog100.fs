#version 100

precision mediump float;

varying vec2 fragTexCoord;
varying vec4 fragColor;

uniform vec2 fogCenter;
uniform float fogRadius;

void main() {
  float inner = fogRadius * 0.7;

  float alpha = 1.0;
  vec2 pos = vec2(gl_FragCoord.x, gl_FragCoord.y);

  float d = distance(pos, fogCenter);
  if (d > fogRadius) alpha = 1.0;
  else {
    if (d < fogRadius * 0.7) alpha = 0.0;
    else alpha = (d - inner) / (fogRadius - inner);
  }

  gl_FragColor = vec4(0.0, 0.0, 0.0, alpha);
}
