in vec2 vertex2f;

void main() {
	gl_Position = gl_ModelViewProjectionMatrix * vec4(vertex2f, 0.0, 1.0);
}