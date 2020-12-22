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
              struct = list()
              macro = list()
              enum = list()
              
              if i.tag == "macro" :
                  
                  for j in i:
                      macro.append( (j.get('name'), j.get('val'))   )
                  self.macros.append((i.get('name'),macro))
                  
              elif  i.tag== "enum":     
                  for j in i:
                      enum.append(  (j.get('name'), j.get('val'))      )
                  self.enums.append(  (i.get('name'),enum)  )
              elif i.tag == "struct" :

                  for j in i:
                      struct.append( (j.get('type'), j.get('name')) )
                      #print( (j.get('type'), j.get('name')) )
                        
                  self.structs.append(  (i.get('name'),struct) )
              
              

    
    
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
        elif self.check_method == "crc16" or self.check_method == "sum16":
            crc_reserve_bytes = "2"
        elif self.check_method == "crc32" or self.check_method == "sum32":
            crc_reserve_bytes = "4"
        
        
        msg = ""
        msg += '%s \"%s.h\"\n' % ("#include", "packet")  #include "xxx.h"
      
        
        #msg += "#define PACK_SEND packet_send(uint8_t* data,uint16_t len);\n"
        for struct in self.structs:
            struct_name = struct[0]
            msg +=  '%s_t %s;\n' % (struct_name, struct_name)
        
        
        f = QtCore.QFile('qrc:/source/crc8.c')
        if f.open(QFile.ReadOnly):
            #content = str(f.readAll(), 'utf-8')
           
            print(f.readAll())
            f.close()
        else:
            print(f.errorString())
        
        #crc_function
        msg += "uint32_t sum32(uint8_t*data, uint16_t len){\n"\
                "\t uint32_t sum = 0x0000;\n"\
                "\t for(uint16_t i=0;i<len;i++){\n"\
                "\t\t sum+= data[i];\n"\
                "\t } \n"\
                "\t return sum;\n"\
                "}\n"

        # check function
        msg += "uint16_t check_function(uint8_t *data, uint8_t* pack,uint16_t len){\n" \
                    "\t return %s(pack, len);\n"\
                "}\n\n" % (self.check_method)
        
        ## encode
        for struct in self.structs:
            struct_name = struct[0]
            msg +="uint16_t %s_encode(uint8_t* data, %s_t* pack, uint16_t len){\n" %( struct_name,     struct_name  )
            msg += "\t memset(data, 0 , %s);\n" % ("PACK_LEN")
            msg += "\t memcpy(data,pack,sizeof(%s_t));\n" %(struct_name)
            msg += "\t pack->len = sizeof(packet1_t)-1-1;\n"
            msg += "\t pack->checksum = check_function(data,pack, (sizeof(%s_t) -%s));\n" %(struct_name,crc_reserve_bytes)
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
        
        
        
        
        self.cfile_txt.setText(msg)


    def generate_hfile(self):
        
        msg = ""
        msg += "#include \"stdint.h\"  \n"
        msg += "#ifndef __PACKET_H_ \n"
        msg += "#define __PACKET_H_ \n"
        
        
       
        # print macros
        for macro in self.macros :
            macro_name = macro[0]
            macro_vars = macro[1]
            msg += "/* "  +  macro_name + " macros" + " */ \n"
            
            for var in macro_vars :
                msg += "#define" + "\t" +  var[0] + "\t" + var[1]  + "\n" 
        
        
        # print enumeration
        for enum in self.enums:
            enum_name = enum[0]
            enum_vars = enum[1]
            msg+= "/* "  +  macro_name + " enumeration" + " */ \n"
            msg+= "enum "+ enum_name  +"{\n"
            for  var in enum_vars:
                msg += "\t" + var[0] + " = " +var[1] + ",\n"
            
            msg+= "\n};\n"
        
        
        
        msg += "#pragma pack(push,1)\n"
        # print structs  //struct pack  little/big endian
        for struct in self.structs:
            struct_name = struct[0]
            struct_vars = struct[1]
            msg += "\n"
            msg += "typedef struct "  + struct_name + "_struct{\n\n"

            for var in struct_vars:
                msg+="\t" + var[0] + " " + var[1]+ ";\n"
            msg += "\n}"+ struct_name +"_t;\n"
                
        msg += "\n"
        msg += "#pragma pack(pop)\n"
        msg += "\n"
        msg += "#endif\n"
        
        
        self.hfile_txt.setText(msg)







if __name__=="__main__":
    app = QApplication(sys.argv)
    ex=MyForm()
    ex.show()
    sys.exit(app.exec_())











