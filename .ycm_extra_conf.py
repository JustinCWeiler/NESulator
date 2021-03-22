def Settings(**kwargs):
    return {
        'flags': [
            '-std=c99',
            '-Wall',
            '-Wextra',
            '-Og',
            '-Iinclude',
            '-lSDL2'
        ]
    }
