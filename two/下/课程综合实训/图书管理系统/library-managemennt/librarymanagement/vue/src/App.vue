$route:any
<template>
  <div id="app">

    <!-- 如何加注释-->
    <!--  头部区域 -->
    <div id="header" style="height: 60px; line-height: 60px; background-color: navajowhite; margin-bottom:2px">
      <img src="@/assets/logo.png" alt="" style="width: 40px; position: relative;top:10px;left: 20px ">
      <span style="margin-left: 30px; font-size:24px">图书管书籍管理系统</span>
    </div>
    <!-- 图片Logo-->



    <!--侧边栏主体 -->
    <div  style="display: flex ">
      <!--侧边栏导航 -->
      <div  style="width: 200px ;min-height:calc(100vh - 62px);overflow:hidden ;margin-right: 2px; background-color: white">
        <!-- 这里直接使用了elementui的框架-->
        <!-- default-openend数组，可以设置当前默认打开的submenu -->

        <el-menu :default-active="this.$route.path" :default-openeds="['1']" class="el-menu-demo" router>
          <!-- 每个Index都是一个页面，会进行跳转-->
          <el-menu-item index="/">首页</el-menu-item>
            <i class="el-icon-eleme"></i>
          <span>首页</span>
          <el-submenu index="1">
            <template slot="title">关于页面</template>
            <el-menu-item index="/about">关于详情</el-menu-item>
          </el-submenu>
        </el-menu>


      </div>

      <!-- 主体数据 -->
      <div  style="flex: 1;background-color: white ; padding:10px ">
        <router-view/>
      </div>

    </div>


  </div>
</template>


<script lang="ts">

</script>