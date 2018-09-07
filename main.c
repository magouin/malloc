int main(){
	char * ptr;
	char *ptr2;
	ptr = malloc(14);
	memcpy(ptr, "abcdefghijklm", 14);
	realloc(ptr, 16);
	memcpy(ptr, "abcdefghijklmno", 16);
	free(ptr);
}
