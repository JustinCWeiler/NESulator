def Settings(**kwargs):
    return {
        'flags': [
            '-std=c99',
            '-Wall',
            '-Wextra',
            '-Werror',
            '-Og',
            '-Iinclude'
        ]
    }
