#include <stdio.h>
#include <string.h>

int parse_url(const char* url);

int main() {
    printf("Test 1: Normal URL\n");
    parse_url("https://example.com/search?name=John&age=30&city=New+York");
    
    printf("\nTest 2: No query parameters\n");
    parse_url("https://example.com/search");
    
    printf("\nTest 3: Empty values\n");
    parse_url("https://example.com/search?key1=&key2=value");
    
    printf("\nTest 4: Multiple ampersands\n");
    parse_url("https://example.com/search?&&a=1&&b=2&");
    
    printf("\nTest 5: Special characters\n");
    parse_url("https://example.com/search?email=user%40example.com&name=John+Doe");
    
    return 0;
}
