import xmltodict
import pprint
import json

my_xml = """
<file name="packet">
    <macro name = "pack">
        <var name = "PACK_LEN" val = "200" brief="the legnth">  </var>
    </macro>
    
    <enum name = "device_type">
         <var name = "mattress" val = "0"> </var>
        <var name = "spine" val = "1"> </var>
        <var name = "//reserved" val = "2"> </var>
    </enum>
    
    <enum name = "packet_type">
        <var name = "position" val = "0"> </var>
        <var name = "adjoint" val = "1"> </var>
        <var name = "massage" val = "2"> </var>
        <var name = "meditation" val = "3"> </var>
        <var name = "hardness" val = "4"> </var>
        <var name = "//reserved" val = "5"> </var>
    </enum>
    
    <enum name = "sub_bed">
        <var name = "all" val = "0"> </var>
        <var name = "left" val = "1"> </var>
        <var name = "right" val = "2"> </var>
        <var name = "//reserved" val = "3"> </var>
    </enum>
    
    
    <enum name = "joint_mode">
        <var name = "off" val = "0"> </var>
        <var name = "joint" val = "1"> </var>
        <var name = "disjoint" val = "2"> </var>
        <var name = "free_mode" val = "3"> </var>
    </enum>
    
    <enum name = "meditation_mode">
        <var name = "meditation_on" val = "0"> </var>
        <var name = "meditation_lv1" val = "1"> </var>
        <var name = "meditation_lv2" val = "2"> </var>
        <var name = "meditation_lv3" val = "3"> </var>
        <var name = "meditation_off" val = "4"> </var>
        <var name = "//reserved" val = "5"> </var>
    </enum>
    
    <!--uart-->
    <union name = "joint" anonymous_type = "uint8_t">
        <struct>
            <var type="uint8_t" name="header_leg" bit ="1"> </var>
            <var type="uint8_t" name="pillow" bit ="1"> </var>
            <var type="uint8_t" name="neck" bit ="1"> </var>
            <var type="uint8_t" name="back" bit ="1"> </var>
            <var type="uint8_t" name="lumbar" bit ="1"> </var>
            <var type="uint8_t" name="buttocks" bit ="1"> </var>
            <var type="uint8_t" name="reserved" bit ="1"> </var>
        </struct>
    </union>
    

    <struct name = "header" encode = "false" config = "true">
        <var type="uint8_t" name="header"> </var>
        <var type="uint8_t" name="len"> </var>
    	<var type="uint8_t" name="packet_type"> </var>
    	<var type="uint8_t" name="device_type"> </var>
        <var type="uint8_t" name="msg_id"> </var>
        <var type="uint8_t" name="sub_bed"> </var>
    </struct>  
    
    <struct name = "data" encode = "false" config = "true">
        <var type = "uint8_t" name = "position"></var>
        <var type = "uint8_t" name = "hardness"></var>
        <var type = "joint_u" name = "joint"></var>
        <var type = "uint8_t" name = "massage"></var>
        <var type = "uint8_t" name = "massage_level"></var>
        <var type = "uint8_t" name = "meditation"></var>
    	<var type = "uint8_t" name = "meditation_level"></var>
    </struct>
    
    <struct name = "packet" encode = "true" config="true">
        <var type="header_t" name="header"> </var>
        <var type="data_t" name = "data"></var>
        <var type = "uint32_t" name = "checksum" ></var>
    </struct>  

    <struct name = "packet_ack" encode = "true" config = "true">
       <var type="header_t" name="header"> </var>
       <var type="uint8_t" name="valid"></var>
       <var type="uint8_t" name="status"></var>
       <var type="uint8_t" name="hardness"></var>
       <var type = "uint32_t" name = "checksum" ></var>
    </struct>
</file>
"""

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
    
        

