import os

class genc:
    
    def __init__(self):
        print("genc init")
        #default setting
        self.use_doxygen_cmd = True
        self.checksum_method = "sum32"
        self.endian = "little-endian"
        self.align = 1
        
        pass
    def pass_dict(self,data):
        print("parser c")
        pass
    def set_checksum_method(self,method):
        if method == "sum8":
            pass
        elif method == "sum16":
            pass
        elif method == "sum32":
            pass
        elif method == "crc8":
            pass
        elif method == "crc16":
            pass
        elif method == "crc32":
            pass
    def set_doxygen_cmd(self,flag):
        if flag == True:
            pass
        else:
            pass
    def set_endian(self,endian):
        if endian == "little-endian":
            self.endian = "little-endian"
        elif endian == "big-endian":
            self.endian = "big-endian"
    def set_align(self,align):
        if align ==1:
            self.align = str(align)
        elif align ==2:
            self.align = str(align)
        elif align ==3:
            self.align = str(align)
        elif align ==4:   
            self.align = str(align)
    def gen_header_file(self):
        txt = ""
        txt+= '#include <>'
        return txt
    

    
    def gen_source_file(self):
        txt = ""
        txt+= '#include <>'
        return txt    
    
    