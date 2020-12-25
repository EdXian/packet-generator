import sys 
from PyQt5 import QtGui, QtCore
from PyQt5.QtGui import QColor, QPalette
from PyQt5.QtCore import QDate, QTime, QDateTime, Qt,QFile
from PyQt5.QtWidgets import QApplication, QWidget, QInputDialog, QLineEdit, QFileDialog, QMessageBox
from PyQt5.QtWidgets import* 
from PyQt5.uic import loadUi
import serial.tools.list_ports
from serial import SerialException
import serial
import struct
import os
import sys
import glob
from dataclasses import dataclass
import xml.etree.ElementTree as ET

import resource




class MyForm(QMainWindow):
    def __init__(self):
        QMainWindow.__init__(self)
        loadUi("form.ui",self)
        
        #self.struct = list() 
        self.structs = list()
        self.macros = list()
        self.enums = list()
        self.unions = list()
        
        self.gen_Button.clicked.connect(self.generate_pack)
        self.load_xml_Button.clicked.connect(self.load_xml_file)
        self.hfile_txt.setFont(QtGui.QFont('Arial', 15))
        self.cfile_txt.setFont(QtGui.QFont('Arial', 15))
        
        
        self.check_method = self.check_method_comboBox.currentText()
        self.endian = self.endian_comboBox.currentText()
        self.align = self.align_comboBox.currentText()
        self.pack_attr = self.pack_attr_comboBox.currentText()
       

    def update_config(self):
        self.check_method = self.check_method_comboBox.currentText()
        self.endian = self.endian_comboBox.currentText()
        self.align = self.align_comboBox.currentText()
        self.pack_attr = self.pack_attr_comboBox.currentText()
        
    def load_xml_file(self):
        options = QFileDialog.Options()
        options |= QFileDialog.DontUseNativeDialog
        
        self.app_file_location, _ = QFileDialog.getOpenFileName(self,"QFileDialog.getOpenFileName()", "","Python Files (*.xml);;All Files (*)", options=options)
        self.file_lineEdit.setText(self.app_file_location)
        try :
            if self.app_file_location:
               self.xml_tree = ET.parse(self.app_file_location)
               self.parse_xml()
               #QMessageBox.critical(self, 'Error', 'parse xml failed', QMessageBox.Yes | QMessageBox.No, QMessageBox.No)

        except:
            QMessageBox.critical(self, 'Error', 'parse xml failed', QMessageBox.Yes | QMessageBox.No, QMessageBox.No)

      
           
           
    def parse_xml(self):   
        if self.xml_tree :
            root = self.xml_tree.getroot()
            #structs 
            
            self.structs.clear()
            count =0
            for i in root: 

              if i.tag == "macro" :
                  macro = list()
                  for j in i:
                      macro.append( (j.get('name'), j.get('val'))   )
                  self.macros.append((i.get('name'),macro))

              elif  i.tag== "enum":
                  enum = list()
                  for j in i:
                      enum.append(  (j.get('name'), j.get('val'))      )
                  self.enums.append(  (i.get('name'),enum)  )
                  
              elif  i.tag ==  "union":
                  union = list()
                  for j in i:
                      
                      if j.tag == "struct":
                          struct_in_union = list()
                          for k in j : 
                              if k.get('type') !="":
                                  struct_in_union.append(  (k.get('type'), k.get('name'), k.get('bit') ) )
                      union.append( struct_in_union )
                  
                  self.unions.append( (i.get('name'),i.get('anonymous_type') ,union) )    
                  #print(self.unions)
                 
                    
              elif i.tag == "struct" :
                  struct = list()
                  for j in i:
                      struct.append( (j.get('type'), j.get('name')) )
                      #print( (j.get('type'), j.get('name')) )      
                  self.structs.append(  (i.get('name'),struct,i.get('encode'),i.get('config')) )
              
              

    
    
    def generate_pack(self):
        
        self.cfile_txt.setText("")
        self.hfile_txt.setText("")
        
        self.generate_cfile()
        self.generate_hfile()                       
             
    def generate_decode_handle(msg):
    
         return msg  
         
    def generate_encode_handle(msg):
        
         
         pass              
   
    def generate_cfile(self):
        
        self.update_config()
        
        if self.check_method == "crc8" or self.check_method == "sum8":
            crc_reserve_bytes = "1"
            crc_return_type = "uint8_t"
        elif self.check_method == "crc16" or self.check_method == "sum16":
            crc_reserve_bytes = "2"
            crc_return_type = "uint16_t"
        elif self.check_method == "crc32" or self.check_method == "sum32":
            crc_reserve_bytes = "4"
            crc_return_type = "uint32_t"
        
        msg = ""
        msg += ''
        
        msg += '#include \"%s.h\"\n' % ("packet")  #include "xxx.h"
        
        ''' 
        for struct in self.structs:
            struct_name = struct[0]
            msg +=  '%s_t %s;\n' % (struct_name, struct_name)
        '''
        
        path = "source/%s.c" %(self.check_method)
        f_check_func = open(path, "r").read()
        
        
        #crc_function
        msg += f_check_func
        msg += "\n"
        
        # check function
        msg += "%s check_function(uint8_t* pack,uint16_t len){\n" \
                    "\t return %s(pack, len);\n"\
                "}\n\n" % ((crc_return_type),self.check_method)
        
        ## input argument
        for struct in self.structs:
            struct_name = struct[0]
            context = struct[1]
            struct_config = struct[3]
            arg = ""
            statement = "\t\n"
            if struct_config == "true":
                for i in context:
                    statement += "\t pack->%s = %s;\n" % (i[1],i[1])
                    if i == context[-1]:  # if the last 1
                        arg += "\n\t      %s %s" %(i[0],i[1])
                    else:
                        arg += "\n\t      %s %s," %(i[0],i[1])
                msg +="void %s_config(%s_t* pack,%s){\n" %(struct_name,struct_name,arg)
                msg += statement
                msg += "\n}\n"

        ## encode
        for struct in self.structs:
            struct_name = struct[0]
            struct_encode = struct[2]
            if struct_encode == "true":
                msg +="uint16_t %s_encode(uint8_t* data, %s_t* pack, uint16_t len){\n" %( struct_name,     struct_name  )
                msg += "\t memset(data, 0 , %s);\n" % ("PACK_LEN")
                msg += "\t memcpy(data,pack,sizeof(%s_t));\n" %(struct_name)
                msg += "\t pack->header.len = sizeof(%s_t)-1-1;\n" %(struct_name)
                msg += "\t pack->checksum = check_function(pack, (sizeof(%s_t) -%s));\n" %(struct_name,crc_reserve_bytes)
                msg += "\t return sizeof(%s_t);\n"%(struct_name)
                msg += "\n\n\n"
                msg += "}\n" 




        # send
        '''
        msg += "uint16_t uart_send(uint8_t *data,uint16_t len){\n" \
                    "\t "\
                "}\n\n" 
        '''
        ## decode
        
        ## IRQ_Handler
        
        ## main function
        
        
        
        
        self.cfile_txt.setText(msg)


    def generate_hfile(self):
        pack_attr_front = ""
        pack_attr_end  = ""
        self.update_config()
     
        #if self.pack_attr  == "pragma":
        #    pack_attr_front = "#pragma pack(push,%s)\n" %(self.align)
        #    pack_attr_end = "#pragma pack(pop)\n"
        
        
        
        msg = ""
        msg += "#include \"stdint.h\"  \n"
        #msg += "#pragma once"
        msg += "#ifndef __PACKET_H_ \n"
        msg += "#define __PACKET_H_ \n"
        
        
       
        # print macros
        for macro in self.macros :
            macro_name = macro[0]
            macro_vars = macro[1]
            msg += "/* "  +  macro_name + " macros" + " */ \n"
            
            for var in macro_vars :
                msg += "#define" + "\t" +  var[0] + "\t" + var[1]  + "\n" 
        
        msg += "\n"
        msg+= "/* "  +  macro_name + " enumeration" + " */ \n"
        # print enumeration
        for enum in self.enums:
            enum_name = enum[0]
            enum_vars = enum[1]
            
            msg+= "typedef enum "+ enum_name  +"{\n"
            for  var in enum_vars:
                msg += "\t" + var[0] + " = " +var[1] + ",\n"
            
            msg+= "\n}%s_e;\n" %(enum_name)
        
        msg += "\n"       
        
        msg += pack_attr_front
        
        # print unions 
        for union in self.unions:
            union_name = union[0]
            union_type = union[1]
            union_vars = union[2]
            msg += "\n"
            msg += "typedef union %s_union{\n\n" %(union_name)
            
            for structs in union_vars:
               
                msg += " struct {\n"
                for var in structs:
                    msg += "\t%s %s : %s;\n" %(var[0],var[1],var[2])
                msg += "\t};\n"
            msg += "\t%s %s_value;\n"%(union_type, union_name)
            msg +=  "\n}%s_u;\n"%( union_name)
                    
                    
        # print structs  //struct pack  little/big endian
        for struct in self.structs:
            struct_name = struct[0]
            struct_vars = struct[1]
            msg += "\n"
            if self.pack_attr == "pragma":
                msg += "#pragma pack(%s)\n"%(self.align)
                msg += "#pragma scalar_storage_order %s-endian\n" %(self.endian)
            elif self.pack_attr == "attr":
                msg += "__attribute__((packed, aligned(%s), scalar_storage_order(\"%s\")))" %(self.align, self.endian)
            
            
            msg += "typedef struct "  + struct_name + "_struct{\n\n"
            for var in struct_vars:
                msg+="\t" + var[0] + " " + var[1]+ ";\n"
            msg += "\n}"+ struct_name +"_t;\n"
                
        msg += "\n"
        
        msg += pack_attr_end
        
        msg += "\n"
        
        ## funciton declaration
        #msg += "void"
        
        
        msg += "#endif\n"
        
        
        self.hfile_txt.setText(msg)




if __name__=="__main__":
    app = QApplication(sys.argv)
    ex=MyForm()
    ex.show()
    sys.exit(app.exec_())











