#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>

#define array_size(a) sizeof(a)/sizeof(a[0])
#define alphabet_size (26)
#define char_to_index(c) ( (int)c - (int)'a' )

struct trie_node{
    struct trie_node *children[alphabet_size];
    bool end_of_word;
};

struct trie_node *get_node(){ 
    struct trie_node *p_node = NULL;
    p_node = (struct trie_node*)malloc(sizeof(struct trie_node));
    if(p_node){
        int i;
        p_node->end_of_word=false;
        for(int i=0;i<alphabet_size;i++){
            p_node->children[i]=NULL;
        }
    }
    return p_node;
}

void insert(struct trie_node *root,const char *key){
    int height; 
    int lenght = strlen(key); 
    int index; 

    struct trie_node *p_crawl = root;
    for(height=0; height<lenght; height++){
        index = char_to_index(key[height]);
        if(!p_crawl->children[index])
            p_crawl->children[index] = get_node();
        p_crawl=p_crawl->children[index];
    }
    p_crawl->end_of_word=true;
}

bool search(struct trie_node *root, const char *key){
    int height; 
    int lenght = strlen(key); 
    int index; 

    struct trie_node *p_crawl = root;
    for(height=0; height<lenght; height++){
        index = char_to_index(key[height]);
        if(!p_crawl->children[index])
            return false;
        p_crawl=p_crawl->children[index];
    }
    return (p_crawl!= NULL && p_crawl->end_of_word);
}

void main(){
    char output[][5] = {"false", "true"};
    FILE *f_ptr;
    int n;
    f_ptr = fopen("testing.txt","r");
    if(f_ptr=NULL){
        printf("file does not exist\n");
        return;
    }
    fscanf(f_ptr,"%n", &n);
    struct trie_node *root = get_node();
    char str[50];
    for(int i=0;i<n;i++){
        fscanf(f_ptr,"%s", str);
            insert(root, str);
        }
    
    printf("%d",search(root,"march\n"));
}