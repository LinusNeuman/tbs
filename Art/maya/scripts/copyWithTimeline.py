mesh = "longJohnMesh"

for frame in range(0,192):
    cmds.currentTime(frame)
    copyMesh = n="%s_%d" % (mesh, frame)
    cmds.duplicate(mesh,n=copyMesh)
    #cmds.select(copyMesh,r=True)
    cmds.parent(copyMesh,"snaps")