from PIL import Image
def Get_User_Ic(file, save_path):
    img = Image.open(file)
    width, height = img.size
    cropped_image = None
    if width > height:
        top = 0
        bottom = height
        left = (width - height) / 2
        right = left + height
        cropped_image = img.crop((left, top, right, bottom))
    else:
        left = 0
        right = width
        top = (height - width) / 2
        bottom = top + width
        cropped_image = img.crop((left, top, right, bottom))
    cropped_image=cropped_image.resize((256, 256))
    # cropped_image.save(save_path+".jpg")
    cropped_image.save("user_ic/"+save_path)