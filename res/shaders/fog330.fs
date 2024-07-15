#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform vec2 fogCenter;
uniform float fogRadius;

out vec4 finalColor;

void main() {
  float inner = fogRadius * 0.7f;

  float alpha = 1.0f;
  vec2 pos = vec2(gl_FragCoord.x, gl_FragCoord.y);

  float d = distance(pos, fogCenter);
  if (d > fogRadius) alpha = 1.0f;
  else {
    if (d < fogRadius * 0.7f) alpha = 0.0f;
    else alpha = (d - inner) / (fogRadius - inner);
  }

  finalColor = vec4(0, 0, 0, alpha);
}
