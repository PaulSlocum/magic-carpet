//
//  ViewController.m
//  OpenGL
//
//  Created by Paul Slocum on 12/27/18.
//  Copyright © 2018 Paul Slocum. All rights reserved.
//


// ORIGINAL
/* #import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end //*/


#import "ViewController.h"

typedef struct {
    
    GLKVector3 PositionCoordinates;
    
}VertexData;

#define SQUARE_SIZE 120.0f

VertexData Vertices[] = {
    
    {0.0f, 0.0f, 0.0f},
    {SQUARE_SIZE, 0.0f, 0.0f},
    {0.0f, SQUARE_SIZE, 0.0f},
    {0.0f, SQUARE_SIZE, 0.0f},
    {SQUARE_SIZE, 0.0f, 0.0f},
    {SQUARE_SIZE, SQUARE_SIZE, 0.0f}
};

@interface ViewController ()

@property (nonatomic, strong) EAGLContext *Context;
@property (nonatomic, strong) GLKBaseEffect *BaseEffect;

@end

@implementation ViewController {
    
    GLuint _VertexBufferID;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.Context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    
    GLKView *View = (GLKView *)self.view;
    View.context = self.Context;
    [EAGLContext setCurrentContext:self.Context];
    
    self.BaseEffect = [[GLKBaseEffect alloc] init];
    self.BaseEffect.useConstantColor = YES;
    self.BaseEffect.constantColor = GLKVector4Make(0/255.0f, 255/255.0f, 255/255.0f, 1.0f);
    
    self.BaseEffect.transform.projectionMatrix = GLKMatrix4MakeOrtho(0, self.view.bounds.size.width, 0, self.view.bounds.size.height, 0, 100);
    
    glClearColor(255/255.0f, 0/255.0f, 0/255.0f, 1.0f);
    
    glGenBuffers(1, &_VertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, _VertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(GLKVertexAttribPosition);
    glVertexAttribPointer(GLKVertexAttribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), NULL);
}

#pragma mark - GLKView delegate methods

-(void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    
    glClear(GL_COLOR_BUFFER_BIT);
    [self.BaseEffect prepareToDraw];
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

-(void)Update {
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
