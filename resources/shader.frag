
uniform vec2 lightPositions[10];  // Assuming 2 lights, adjust size as needed
uniform float lightRadiuss[10];     // Assuming 2 lights, adjust size as needed

void main()
{
    vec2 fragPosition = gl_FragCoord.xy; 

    float minDistance = 99999.0;  // Initialize with a large number

    // Loop through each light position and calculate distance
    for (int i = 0; i < 2; ++i) { // Assuming 2 lights
        float distance = length(fragPosition - lightPositions[i]);
        float normalizedDistance = distance / lightRadiuss[i];
        minDistance = min(minDistance, normalizedDistance);
    }

    gl_FragColor.a = minDistance;
}