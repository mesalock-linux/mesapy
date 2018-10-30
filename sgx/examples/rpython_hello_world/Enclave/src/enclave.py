def entry_point(args):
    print "Hello, World!"
    return 0

def target(*args):
    return entry_point, None
