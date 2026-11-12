#include "buffer.h"

int main(void) {
    struct MessageBuffer buffer = {0};
    add_message(&buffer, "Hello");
    add_message(&buffer, "World");
    add_message(&buffer, "Is");
    add_message(&buffer, "Awesome");
    print_messages(&buffer);
    return 0;
}