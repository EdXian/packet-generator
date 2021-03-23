import xmltodict
import json


class parser_to_dict:
    def __init__(self):
        self.tdict = []
        self.xml_txt = ""
    
    def set_xml_txt(self,data):
        
        my_dict = xmltodict.parse(data)
        self.tdict =my_dict
        '''
        print(my_dict["file"]["@name"])

        for i in my_dict['file']["enum"]:
            print("---------")
            print(i["@name"])
            for j in i["var"]:
                print(j["@name"],j["@val"])

        s = my_dict["file"]["union"]
        print(s['@name'],s['@anonymous_type'])
        for j in s['struct']['var']:
            print(j["@type"],j["@name"],j["@bit"])
            #print(i["@name"],i["@anonymous_type"])
            #for j in i:
        # struct
        for i in my_dict["file"]["struct"]:    
            print("------------")
            print(i["@name"], i["@encode"], i["@config"])
            for j in i["var"]:
                print(j["@type"], j["@name"])
        '''
 
    def get_macro(self,data):
        pass
    
    def get_enum(self):
        data = ""
        try:
            data = self.tdict['file']["enum"]
            return data
        except:
            return None
    
    
    def get_structure(self):
        data = ""
        try:
            
            data = self.tdict["file"]["struct"]
            return data
        
        except:
            
            return None
        
    def get_union(self):        
        data = ""
        try:
            data = self.tdict["file"]["union"]
            return data
        except:
            return None
    


'''
my_dict = xmltodict.parse(my_xml)
print(my_dict["file"]["@name"])

for i in my_dict['file']["enum"]:
    print("---------")
    print(i["@name"])
    for j in i["var"]:
        print(j["@name"],j["@val"])

s = my_dict["file"]["union"]
print(s['@name'],s['@anonymous_type'])
for j in s['struct']['var']:
    print(j["@type"],j["@name"],j["@bit"])
    #print(i["@name"],i["@anonymous_type"])
    #for j in i:
# struct
for i in my_dict["file"]["struct"]:    
    print("------------")
    print(i["@name"], i["@encode"], i["@config"])
    for j in i["var"]:
        print(j["@type"], j["@name"])
'''    
        

