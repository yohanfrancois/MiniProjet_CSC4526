uniform vec2 lightPosition;
uniform float lightRadius;

void main()
{

    vec2 fragPosition = gl_FragCoord.xy; 

    // Calcule la distance entre la position du fragment et la position de la souris
    float distance = length(fragPosition - lightPosition);

    gl_FragColor.a = distance/lightRadius;

}